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

#include "libvbox_p.h"

COM_WRAP_IFC(IEventSource)

VBox::COMPtr<VBox::IEventListener> VBox::IEventSource::createListener()
{
    ::IEventListener *cResult = nullptr;

    auto rc = get_IFC()->CreateListener(&cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IEventListener>::wrap(cResult);
}

VBox::COMPtr<VBox::IEventSource> VBox::IEventSource::createAggregator(
        const std::vector<COMPtr<IEventSource>> &subordinates)
{
    ::IEventSource *cResult = nullptr;
    COM_ArrayProxy<::IEventSource *> pSubordinates(subordinates);

    auto rc = get_IFC()->CreateAggregator(COM_ArrayParameter(pSubordinates), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IEventSource>::wrap(cResult);
}

void VBox::IEventSource::registerListener(const COMPtr<IEventListener> &listener,
        const std::vector<VBoxEventType> &interesting, bool active)
{
    COM_ArrayProxy<COM_Enum(::VBoxEventType)> pInteresting(interesting);

    auto rc = get_IFC()->RegisterListener(listener->get_IFC(),
                    COM_ArrayParameter(pInteresting), active);
    COM_ERROR_CHECK(rc);
}

void VBox::IEventSource::unregisterListener(const COMPtr<IEventListener> &listener)
{
    auto rc = get_IFC()->UnregisterListener(listener->get_IFC());
    COM_ERROR_CHECK(rc);
}

bool VBox::IEventSource::fireEvent(const COMPtr<IEvent> &event, int32_t timeout)
{
    COM_Bool cResult;

    auto rc = get_IFC()->FireEvent(event->get_IFC(), timeout, &cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

VBox::COMPtr<VBox::IEvent> VBox::IEventSource::getEvent(
        const COMPtr<IEventListener> &listener, int32_t timeout)
{
    ::IEvent *cResult = nullptr;

    auto rc = get_IFC()->GetEvent(listener->get_IFC(), timeout, &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IEvent>::wrap(cResult);
}

void VBox::IEventSource::eventProcessed(const COMPtr<IEventListener> &listener,
        const COMPtr<IEvent> &event)
{
    auto rc = get_IFC()->EventProcessed(listener->get_IFC(), event->get_IFC());
    COM_ERROR_CHECK(rc);
}
