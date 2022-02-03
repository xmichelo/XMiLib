/// \file
/// \author 
///
/// \brief Implementation of version number class.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "VersionNumber.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] major The major version number.
/// \param[in] minor The minor version number.
//**********************************************************************************************************************
VersionNumber::VersionNumber(quint32 major, quint32 minor)
   : major_(major)
   , minor_(minor)
{
}


//**********************************************************************************************************************
/// \param[in] other The version number to copy
//**********************************************************************************************************************
VersionNumber::VersionNumber(VersionNumber const& other)
   : major_(other.major_)
   , minor_(other.minor_)
{
}


//**********************************************************************************************************************
/// \param[in] other the version number to copy.
//**********************************************************************************************************************
VersionNumber::VersionNumber(VersionNumber&& other) noexcept
   : major_(other.major_)
     , minor_(other.minor_)
{
}


//**********************************************************************************************************************
/// \param[in] other The version number to copy.
/// \return A reference to the copy.
//**********************************************************************************************************************
VersionNumber& VersionNumber::operator=(VersionNumber const& other)
{
   major_ = other.major_;
   minor_ = other.minor_;
   return *this;
}


//**********************************************************************************************************************
/// \param[in] other The version number to copy.
/// \return A reference to the copy.
//**********************************************************************************************************************
VersionNumber& VersionNumber::operator=(VersionNumber&& other) noexcept
{
   major_ = other.major_;
   minor_ = other.minor_;
   return *this;
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if the two version numbers are equal.
//**********************************************************************************************************************
bool VersionNumber::operator==(VersionNumber const& other) const
{
   return (major_ == other.major_) && (minor_ == other.minor_);
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if the two version numbers are equal.
//**********************************************************************************************************************
bool VersionNumber::operator!=(VersionNumber const& other) const
{
   return (major_ != other.major_) || (minor_ != other.minor_);
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if other is strictly inferior to this version number.
//**********************************************************************************************************************
bool VersionNumber::operator<(VersionNumber const& other) const
{
   return (major_ < other.major_) ? true : ((major_ > other.major_) ? false : (minor_ < other.minor_));
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if other is inferior or equal to this version number.
//**********************************************************************************************************************
bool VersionNumber::operator<=(VersionNumber const& other) const
{
   return (major_ < other.major_) ? true : ((major_ > other.major_) ? false : (minor_ <= other.minor_));
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if other is strictly superior to this version number.
//**********************************************************************************************************************
bool VersionNumber::operator>(VersionNumber const& other) const
{
   return (major_ < other.major_) ? false : ((major_ > other.major_) ? true : (minor_ > other.minor_));
}


//**********************************************************************************************************************
/// \param[in] other The other version number to compare to.
/// \return true if and only if other is superior or equal to this version number.
//**********************************************************************************************************************
bool VersionNumber::operator>=(VersionNumber const& other) const
{
   return (major_ < other.major_) ? false : ((major_ > other.major_) ? true : (minor_ >= other.minor_));
}


//**********************************************************************************************************************
/// \param[in] major The major version number.
/// \param[in] minor The minor version number.
//**********************************************************************************************************************
void VersionNumber::setValue(qint32 major, quint32 minor)
{
   major_ = major;
   minor_ = minor;
}


//**********************************************************************************************************************
/// \param[in] major The major version number.
//**********************************************************************************************************************
void VersionNumber::setMajor(quint32 major)
{
   major_ = major;
}


//**********************************************************************************************************************
/// \return The major version number.
//**********************************************************************************************************************
quint32 VersionNumber::major() const
{
   return major_;
}


//**********************************************************************************************************************
/// \param[in] minor The minor version number.
//**********************************************************************************************************************
void VersionNumber::setMinor(qint32 minor)
{
   minor_ = minor;
}


//**********************************************************************************************************************
/// \return The minor version number.
//**********************************************************************************************************************
quint32 VersionNumber::minor() const
{
   return minor_;
}


//**********************************************************************************************************************
/// \return The version number string.
//**********************************************************************************************************************
QString VersionNumber::toString() const
{
   return QString("%1.%2").arg(major_).arg(minor_);
}


} // namespace xmilib
