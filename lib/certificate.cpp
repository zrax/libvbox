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

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(5, 1, 0)
COM_WRAP_IFC(ICertificate)

VBox::CertificateVersion VBox::ICertificate::versionNumber() const
{
    COM_Enum(::CertificateVersion) result;
    COM_GetValue(get_IFC(), VersionNumber, result);
    return static_cast<CertificateVersion>(result);
}

std::u16string VBox::ICertificate::serialNumber() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SerialNumber, result);
    return result;
}

std::u16string VBox::ICertificate::signatureAlgorithmOID() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SignatureAlgorithmOID, result);
    return result;
}

std::u16string VBox::ICertificate::signatureAlgorithmName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SignatureAlgorithmName, result);
    return result;
}

std::vector<std::u16string> VBox::ICertificate::issuerName() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), IssuerName, result);
    return result;
}

std::vector<std::u16string> VBox::ICertificate::subjectName() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), SubjectName, result);
    return result;
}

std::u16string VBox::ICertificate::friendlyName() const
{
    std::u16string result;
    COM_GetString(get_IFC(), FriendlyName, result);
    return result;
}

std::u16string VBox::ICertificate::validityPeriodNotBefore() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ValidityPeriodNotBefore, result);
    return result;
}

std::u16string VBox::ICertificate::validityPeriodNotAfter() const
{
    std::u16string result;
    COM_GetString(get_IFC(), ValidityPeriodNotAfter, result);
    return result;
}

std::u16string VBox::ICertificate::publicKeyAlgorithmOID() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PublicKeyAlgorithmOID, result);
    return result;
}

std::u16string VBox::ICertificate::publicKeyAlgorithm() const
{
    std::u16string result;
    COM_GetString(get_IFC(), PublicKeyAlgorithm, result);
    return result;
}

std::vector<uint8_t> VBox::ICertificate::subjectPublicKey() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), SubjectPublicKey, COM_Byte, result);
    return result;
}

std::u16string VBox::ICertificate::issuerUniqueIdentifier() const
{
    std::u16string result;
    COM_GetString(get_IFC(), IssuerUniqueIdentifier, result);
    return result;
}

std::u16string VBox::ICertificate::subjectUniqueIdentifier() const
{
    std::u16string result;
    COM_GetString(get_IFC(), SubjectUniqueIdentifier, result);
    return result;
}

bool VBox::ICertificate::certificateAuthority() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), CertificateAuthority, result);
    return static_cast<bool>(result);
}

uint32_t VBox::ICertificate::keyUsage() const
{
    COM_ULong result;
    COM_GetValue(get_IFC(), KeyUsage, result);
    return static_cast<uint32_t>(result);
}

std::vector<std::u16string> VBox::ICertificate::extendedKeyUsage() const
{
    std::vector<std::u16string> result;
    COM_GetStringArray(get_IFC(), ExtendedKeyUsage, result);
    return result;
}

std::vector<uint8_t> VBox::ICertificate::rawCertData() const
{
    std::vector<uint8_t> result;
    COM_GetArray(get_IFC(), RawCertData, COM_Byte, result);
    return result;
}

bool VBox::ICertificate::selfSigned() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), SelfSigned, result);
    return static_cast<bool>(result);
}

bool VBox::ICertificate::trusted() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Trusted, result);
    return static_cast<bool>(result);
}

bool VBox::ICertificate::expired() const
{
    COM_Bool result;
    COM_GetValue(get_IFC(), Expired, result);
    return static_cast<bool>(result);
}

bool VBox::ICertificate::isCurrentlyExpired()
{
    COM_Bool cResult;

    auto rc = get_IFC()->IsCurrentlyExpired(&cResult);
    COM_ERROR_CHECK(rc);

    return static_cast<bool>(cResult);
}

std::u16string VBox::ICertificate::queryInfo(int32_t what)
{
    COM_StringProxy pResult;

    auto rc = get_IFC()->QueryInfo(what, &pResult.m_text);
    COM_ERROR_CHECK(rc);

    return pResult.toString();
}
#endif
