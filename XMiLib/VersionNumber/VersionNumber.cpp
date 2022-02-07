/// \file
/// \author 
///
/// \brief Implementation of version number class.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "VersionNumber.h"


namespace {


//**********************************************************************************************************************
/// \param[in] str The string to parse.
/// \param[out] outOk On exit this is true if and only if parsing succeeded.
/// \return if outOk is true on exit, the function return the parsed version number.
//**********************************************************************************************************************
xmilib::VersionNumber versionNumberFromString(QString const& str, bool& outOk)
{
   outOk = false;
   QRegularExpressionMatch const match = QRegularExpression(R"(^(\d+)\.(\d+)$)").match(str);
   if (!match.hasMatch())
   {
      outOk = false;
      return xmilib::VersionNumber();
   }

   xmilib::VersionNumber result;
   result.setMajor(match.captured(1).toInt(&outOk));
   if (outOk)
      result.setMinor(match.captured(2).toInt(&outOk));
   return result;
}


}


namespace xmilib {


//**********************************************************************************************************************
//
//**********************************************************************************************************************
VersionNumber::VersionNumber()
   : major_(-1)
   , minor_(-1)
{
}


//**********************************************************************************************************************
/// \param[in] major The major version number.
/// \param[in] minor The minor version number.
//**********************************************************************************************************************
VersionNumber::VersionNumber(qint32 major, qint32 minor)
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
/// \return true if and only if the version number is valid
//**********************************************************************************************************************
bool VersionNumber::isValid() const
{
   return (major_ >= 0) && (minor_ >= 0);
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
void VersionNumber::setValue(qint32 major, qint32 minor)
{
   major_ = major;
   minor_ = minor;
}


//**********************************************************************************************************************
/// \param[in] major The major version number.
//**********************************************************************************************************************
void VersionNumber::setMajor(qint32 major)
{
   major_ = major;
}


//**********************************************************************************************************************
/// \return The major version number.
//**********************************************************************************************************************
qint32 VersionNumber::major() const
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
qint32 VersionNumber::minor() const
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

//**********************************************************************************************************************
//
//**********************************************************************************************************************
VersionNumber VersionNumber::fromString(QString const& str, bool* outOk)
{
   bool ok = false;
   VersionNumber const result = versionNumberFromString(str, ok);
   if (outOk)
      *outOk = ok;
   return result;
}


} // namespace xmilib
