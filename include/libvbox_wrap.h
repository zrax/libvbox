/* This file is part of libvbox
 * Copyright (C) 2019  Michael Hansen
 *
 * libvbox is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libvbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libvbox; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef _LIBVBOX_WRAP_H
#define _LIBVBOX_WRAP_H

#include <vector>
#include <stdexcept>

#include "libvbox_string.h"

#define VBox_PROPERTY_RO(type, name)            \
    type name() const;

#define VBox_PROPERTY_RW_V(type, name)          \
    type name() const;                          \
    void set_##name(type value);

#define VBox_PROPERTY_RW_R(type, name)          \
    type name() const;                          \
    void set_##name(const type &value);

#define COM_WRAPPED(COMType)                                            \
            typedef COMType COM_Ifc;                                    \
            static const void *get_IID();                               \
            COMType *get_IFC() const { return _get_IFC<COMType>(); }    \
            void set_IFC(COMType *ifc) { _set_IFC(ifc); }

#if defined(VBOX_XPCOM)
class nsISupports;
class nsIException;
#elif defined(VBOX_MSCOM)
struct IUnknown;
struct IErrorInfo;
#endif

namespace VBox
{
    class COMError : public std::runtime_error
    {
    public:
        COMError(uint32_t rc)
            : std::runtime_error(error_message(rc)), m_rc(rc) { }

        uint32_t error_code() const { return m_rc; }

        static LIBVBOX_API std::string error_message(uint32_t rc);

    private:
        uint32_t m_rc;
    };

    template <class Wrapped>
    class COMPtr
    {
    public:
        typedef Wrapped element_type;

        COMPtr() { }
        COMPtr(std::nullptr_t) { }

        COMPtr(const COMPtr<Wrapped> &other) : m_wrap(other.m_wrap)
        {
            if (m_wrap.have_IFC())
                m_wrap.AddRef();
        }

        COMPtr(COMPtr<Wrapped> &&other) : m_wrap(other.m_wrap)
        {
            other.m_wrap.clear_IFC();
        }

        COMPtr<Wrapped> &operator=(std::nullptr_t)
        {
            if (m_wrap.have_IFC())
                m_wrap.Release();
            m_wrap.clear_IFC();
            return *this;
        }

        COMPtr<Wrapped> &operator=(const COMPtr<Wrapped> &other)
        {
            if (other.m_wrap.have_IFC())
                other.m_wrap.AddRef();
            if (m_wrap.have_IFC())
                m_wrap.Release();
            m_wrap = other.m_wrap;
            return *this;
        }

        COMPtr<Wrapped> &operator=(COMPtr<Wrapped> &&other)
        {
            m_wrap = other.m_wrap;
            other.m_wrap.clear_IFC();
            return *this;
        }

        ~COMPtr()
        {
            if (m_wrap.have_IFC())
                m_wrap.Release();
        }

        template <class COM_Ifc>
        static COMPtr<Wrapped> wrap(COM_Ifc *ifc)
        {
            COMPtr<Wrapped> wrapPtr;
            wrapPtr.m_wrap.set_IFC(ifc);
            return wrapPtr;
        }

        Wrapped *operator->() { return &m_wrap; }
        Wrapped &operator*() { return m_wrap; }

        const Wrapped *operator->() const { return &m_wrap; }
        const Wrapped &operator*() const { return m_wrap; }

        operator bool() const { return m_wrap.get_IFC() != nullptr; }

    private:
        Wrapped m_wrap;
    };

    class LIBVBOX_API COMUnknown
    {
    public:
#if defined(VBOX_XPCOM)
        COM_WRAPPED(::nsISupports)
#elif defined(VBOX_MSCOM)
        COM_WRAPPED(::IUnknown)
#endif

        template <class Ifc>
        Ifc *_get_IFC() const { return reinterpret_cast<Ifc *>(m_ifc); }

        template <class Ifc>
        void _set_IFC(Ifc *ifc) { m_ifc = reinterpret_cast<void *>(ifc); }

        bool have_IFC() const { return m_ifc != nullptr; }
        void clear_IFC() { m_ifc = nullptr; }

        uint32_t AddRef();
        uint32_t Release();

        void _QueryInterface(const void *iid, void **pContainer);

        template <class QIfc>
        COMPtr<QIfc> QueryInterface()
        {
            typename QIfc::COM_Ifc *pResult;
            _QueryInterface(QIfc::get_IID(), reinterpret_cast<void **>(&pResult));
            return COMPtr<QIfc>::wrap(pResult);
        }

    private:
        void *m_ifc;
    };

    class LIBVBOX_API COMErrorInfo : public COMUnknown
    {
    public:
#if defined(VBOX_XPCOM)
        COM_WRAPPED(::nsIException)
#elif defined(VBOX_MSCOM)
        COM_WRAPPED(::IErrorInfo)
#endif

        // XPCOM and MSCOM are completely incompatible for their base
        // error type.  However, both seem to have the concept of a
        // description or message, so that's what we wrap here.
        COMString message() const;
    };
}

#endif /* _LIBVBOX_WRAP_H */
