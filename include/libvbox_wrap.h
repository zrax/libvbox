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
#include <string>
#include <stdexcept>

#include "libvbox_vboxsdk_version.h"

#define VBox_PROPERTY_RO(type, name)            \
    type name() const;

#define VBox_PROPERTY_RW_V(type, name)          \
    type name() const;                          \
    void set_##name(type value);

#define VBox_PROPERTY_RW_R(type, name)          \
    type name() const;                          \
    void set_##name(const type &value);

#define VBox_COM_WRAPPED(COMType)                                       \
    typedef COMType COM_Ifc;                                            \
    static const void *get_IID();                                       \
    COMType *get_IFC() const { return reinterpret_cast<COMType *>(m_ifc); } \
    void set_IFC(COMType *ifc) { m_ifc = reinterpret_cast<void *>(ifc); }

#if defined(VBOX_XPCOM)
class nsISupports;
class nsIException;
#elif defined(VBOX_MSCOM)
struct IUnknown;
struct IErrorInfo;
#endif

namespace VBox
{
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
            if (other->have_IFC())
                other->AddRef();
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

        Wrapped *operator->() const { return &m_wrap; }
        Wrapped &operator*() const { return m_wrap; }

        operator bool() const { return m_wrap.have_IFC(); }

    private:
        // Mutable because Wrapped is treated like a pointer, since its
        // only member is an opaque pointer to the wrapped COM object.
        mutable Wrapped m_wrap;
    };

    class LIBVBOX_API COMUnknown
    {
    public:
#if defined(VBOX_XPCOM)
        VBox_COM_WRAPPED(::nsISupports)
#elif defined(VBOX_MSCOM)
        VBox_COM_WRAPPED(::IUnknown)
#endif

        COMUnknown() : m_ifc() { }
        ~COMUnknown() { }

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

    protected:
        void *m_ifc;
    };

    class LIBVBOX_API COMErrorInfo : public COMUnknown
    {
    public:
#if defined(VBOX_XPCOM)
        VBox_COM_WRAPPED(::nsIException)
#elif defined(VBOX_MSCOM)
        VBox_COM_WRAPPED(::IErrorInfo)
#endif

        // XPCOM and MSCOM are completely incompatible for their base
        // error type.  However, both seem to have the concept of a
        // description or message, so that's what we wrap here.
        std::u16string message() const;
    };
}

#endif /* _LIBVBOX_WRAP_H */
