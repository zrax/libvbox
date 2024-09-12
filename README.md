# libvbox

A C++11 wrapper for the VirtualBox COM/XPCOM API.

libvbox provides a way to interact with the VirtualBOX COM interface
without having to deal with the messy MS COM or XPCOM layers directly.
In fact, after building libvbox, client applications do not need any
COM headers, nor the VirtualBox SDK itself.

libvbox currently supports VirtualBox SDK versions 5.0 through 7.1.

## Building

libvbox uses the [CMake](https://cmake.org/) build system.  To build
libvbox, you will also need a version of the
[VirtualBox SDK](https://www.virtualbox.org/wiki/Downloads) matching your
installed VirtualBox application version.  Be sure to specify which version
of the SDK you're using, as this unfortunately cannot be auto-detected due
to limitations in the SDK.

    > cd C:\path\to\libvbox
    > mkdir build
    > cd build
    > cmake .. -DVirtualBoxSDK_DIR=C:/path/to/virtualbox/sdk \
        -DVirtualBoxSDK_VERSION=7.0.20
    > cmake --build .

NOTE: For XPCOM-based platforms, you may also need to specify the path to the
VirtualBox XPCOM library if it isn't auto-detected:

    $ cd /path/to/libvbox
    $ mkdir build
    $ cd build
    $ cmake .. -DVirtualBoxSDK_DIR=/path/to/virtualbox/sdk \
        -DVirtualBoxSDK_VERSION=7.0.20 \
        -DVirtualBox_XPCOM_LIB=/usr/lib/virtualbox/VBoxXPCOM.so
    $ cmake --build .

## Client Examples

**List Machines**
~~~c++
#include <libvbox.h>

auto vboxClient = VBox::virtualBoxClient();
auto vbox = vboxClient->virtualBox();
auto machines = vbox->machines();
for (const auto &machine : machines)
    std::wcout << VBox::utf16ToWide(machine->name()) << std::endl;
~~~

**Launch a VM by name**
~~~c++
#include <libvbox.h>

auto vboxClient = VBox::virtualBoxClient();
auto vbox = vboxClient->virtualBox();
auto session = vboxClient->session();
auto machine = vbox->findMachine(u"Windows");
if (machine) {
    auto progress = machine->launchVMProcess(session, u"gui", {});
    progress->waitForCompletion(-1);
}
~~~

**Event Listener**
~~~c++
#include <libvbox.h>
#include <thread>

auto evSource = someObject->eventSource();
auto listener = evSource->createListener();
evSource->registerListener(listener, {VBox::VBoxEventType::Any}, false);

std::thread event_thread([evSource, listener]() {
    for ( ;; ) {
        auto event = evSource->getEvent(listener, 500);
        if (!event)
            continue;

        std::wcout << L"Got event type " << static_cast<int>(event->type())
                   << std::endl;
        if (auto stateChangedEvent = event->QueryInterface<VBox::IStateChangedEvent>()) {
            std::wcout << L"    State change: "
                       << static_cast<int>(stateChangedEvent->state())
                       << std::endl;
        }
        evSource->eventProcessed(listener, event);
    }
});
~~~

## Enumerations

libvbox wraps all enumerations described in the VirtualBox SDK in a
C++11 `enum class`.  As such, regardless of the underlying COM
implementation, enum values can be accessed by their fully qualified name.

~~~c++
switch (machine->state()) {
case VBox::MachineState::PoweredOff:
    // ...
    break;
}
~~~

## Interfaces

libvbox wraps COM and XPCOM interfaces using the same naming convection
as is used in the manual (that is, methods and attributes are not converted
to upper-case).  Attribute getters use the same name as the attribute,
and setters use the convention `set_`*attribute*`(`*value*`)`.  "out"
parameters are passed by pointer, and can be `nullptr` if the returned value
is not needed (all wrappers test for `nullptr` before setting "out"
parameters, even if the underlying COM class does not).

For Interface types in the API, a COM-aware smart pointer (`VBox::COMPtr`)
is used to manage reference counting.  Generally speaking, all libvbox
interfaces should live only inside a `VBox::COMPtr`, and manual reference
counting should not be necessary.

Note that, unlike in the VirtualBox SDK, the same interface is used
regardless of whether the underlying SDK uses XPCOM or MS COM.

### COMUnknown

For consistency, the base class of all wrapped interfaces is
`VBox::COMUnknown`, which supports the `IUnknown` (MS COM) / `nsISupports`
(XPCOM) interface.  This class contains a pointer to the underlying
interface type, which can be manipulated with `get_IFC()` and `set_IFC()`,
queried for existence with `have_IFC()` and cleared with `clear_IFC()`.
However, most of the time, you should not use these methods and instead
control access via a `VBox::COMPtr` smart pointer instead.

`VBox::COMUnknown` classes also support a template-based `QueryInterface`,
which will return a pointer to the queried type or `nullptr` if the COM
implementation would return `E_NOINTERFACE`.  For example:

~~~c++
auto event = source->getEvent(listener, -1);
if (auto stateChangedEvent = event->QueryInterface<VBox::IStateChangedEvent>()) {
    // Handle stateChangedEvent
}
~~~

### COMErrorInfo

For consistency, the base class for exception interfaces is wrapped as a
`VBOX::COMErrorInfo` class.  Unfortunately, MS COM and XPCOM do not provide
a consistent API for their base exception classes, so the only attribute
provided is a `message`, which maps to `GetMessage()` on XPCOM and
`GetDescription` on MS COM.  The VirtualBox SDK may provide a more detailed
exception object however, which can be gotten by querying the
`VBox::IVirtualBoxErrorInfo` interface:

~~~c++
auto error = VBox::currentError();
if (auto vboxError = error->QueryInterface<VBox::IVirtualBoxErrorInfo>()) {
    // More detailed handling of vboxError
} else {
    // only error->message() available.
}
~~~

## SDK Types

libvbox uses standard C++11/STL types for the following types used in the
SDK manual:

| VirtualBox SDK Type  | libvbox Type |
|----------------------|--------------|
| `boolean`            | `bool`       |
| `octet`              | `uint8_t`    |
| `short`              | `int16_t`    |
| `unsigned short`     | `uint16_t`   |
| `long`               | `int32_t`    |
| `unsigned long`      | `uint32_t`   |
| `long long`          | `int64_t`    |
| `unsigned long long` | `uint64_t`   |
| `wstring`  | [`std::u16string`](https://en.cppreference.com/w/cpp/string/basic_string) |
| `I`*Interface*       | `VBox::COMPtr<VBox::I`*Interface*`>` |
| *Type*`[]` | [`std::vector`](https://en.cppreference.com/w/cpp/container/vector)`<`*Type*`>` |

## Error Handling

With the exception of `E_NOINTERFACE` (see [`COMUnknown::QueryInterface`](#comunknown)
above for details), error result codes from MS COM / XPCOM are raised as
C++ exceptions.  All exceptions are derived from `VBox::COMError`, which
provides the underlying COM result code in `error_code()`, as well as a
textual version of the error enum in
[`what()`](https://en.cppreference.com/w/cpp/error/exception/what).

For common error types returned by the VirtualBox SDK, a subclass exception
will be thrown for easier exception handling by client code:

| Error Code                | libvbox Exception         |
|---------------------------|---------------------------|
| *Generic COM Exceptions*                              |
| `E_NOTIMPL`               | `VBox::ENotImpl`          |
| `E_POINTER`               | `VBox::EPointer`          |
| `E_ABORT`                 | `VBox::EAbort`            |
| `E_FAIL`                  | `VBox::EFail`             |
| `E_ACCESSDENIED`          | `VBox::EAccessDenied`     |
| `E_OUTOFMEMORY`           | `VBox::EOutOfMemory`      |
| `E_INVALIDARG`            | `VBox::EInvalidArg`       |
| `E_UNEXPECTED`            | `VBox::EUnexpected`       |
| *VirtualBox specific Exceptions*                      |
| `E_OBJECT_NOT_FOUND`      | `VBox::EObjectNotFound`   |
| `E_INVALID_VM_STATE`      | `VBox::EInvalidVMState`   |
| `E_VM_ERROR`              | `VBox::EVMError`          |
| `E_FILE_ERROR`            | `VBox::EFileError`        |
| `E_IPRT_ERROR`            | `VBox::EIPRTError`        |
| `E_PDM_ERROR`             | `VBox::EPDMError`         |
| `E_INVALID_OBJECT_STATE`  | `VBox::EInvalidObjectState` |
| `E_HOST_ERROR`            | `VBox::EHostError`        |
| `E_NOT_SUPPORTED`         | `VBox::ENotSupported`     |
| `E_XML_ERROR`             | `VBox::EXMLError`         |
| `E_INVALID_SESSION_STATE` | `VBox::EInvalidSessionState` |
| `E_OBJECT_IN_USE`         | `VBox::EObjectInUse`      |
| `E_PASSWORD_INCORRECT`    | `VBox::EPasswordIncorrect` |
| `E_MAXIMUM_REACHED`       | `VBox::EMaximumReached`   |
| `E_GSTCTL_GUEST_ERROR`    | `VBox::EGstctlGuestError` |
| `E_TIMEOUT`               | `VBox::ETimeout`          |
| `E_DND_ERROR`             | `VBox::EDndError`         |
| `E_PLATFORM_ARCH_NOT_SUPPORTED` | `VBox::EPlatformArchNotSupported` |
| `E_RECORDING_ERROR`       | `VBox::ERecordingError`   |

## libvbox Entry Points and Helpers

### VBox::virtualBoxClient

To get started with libvbox, one must first acquire the `IVirtualBoxClient`
interface from `VBox::virtualBoxClient()`.  The first call to this function
will initialize the MS COM or XPCOM API and acquire the required VirtualBox
SDK objects.  At the end of the application lifetime, libvbox will clean
itself up automatically.

### VBox::currentError

If a [`VBox::COMError`](#error-handling) exception is thrown, the COM
exception class for the current thread can be obtained with
`VBox::currentError()`.  This function will also clear the current error in
the appropriate manner for the COM implementation.

~~~c++
try {
    auto machine = vbox->findMachine(u"Foobar");
} catch (const VBox::COMError &err) {
    auto errorInfo = VBox::currentError();
    // Display error information...
}
~~~

### VBox::utf16ToUtf8

* `std::string VBox::utf16ToUtf8(const std::u16string &)`
* `std::string VBox::utf16ToUtf8(const char16_t *, size_t)`
* `std::string VBox::utf16ToUtf8(const char16_t *)`

Use the platform's native routines (XPCOM or Win32 API) to convert a
libvbox `std::u16string` to UTF-8.

### VBox::utf8ToUtf16

* `std::u16string VBox::utf8ToUtf16(const std::string &)`
* `std::u16string VBox::utf8ToUtf16(const char *, size_t)`
* `std::u16string VBox::utf8ToUtf16(const char *)`

Use the platform's native routines (XPCOM or Win32 API) to convert a
UTF-8 string to `std::u16string` for libvbox.

### VBox::utf16ToWide

* `std::wstring VBox::utf16ToWide(const std::u16string &)`
* `std::wstring VBox::utf16ToWide(const char16_t *, size_t)`
* `std::wstring VBox::utf16ToWide(const char16_t *)`

Convert a libvbox `std::u16string` to wide format (`std::wstring`), as
appropriate for the target operating system.  This function is provided
by libvbox for convenience.

### VBox::wideToUtf16

* `std::u16string VBox::wideToUtf16(const std::wstring &)`
* `std::u16string VBox::wideToUtf16(const wchar_t *, size_t)`
* `std::u16string VBox::wideToUtf16(const wchar_t *)`

Convert a wide string to `std::u16string` for libvbox.  This function is
provided by libvbox for convenience.
