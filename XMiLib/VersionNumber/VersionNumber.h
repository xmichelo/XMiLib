/// \file
/// \author 
///
/// \brief Declaration of version number class.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#ifndef XMILIB_VERSION_NUMBER_H
#define XMILIB_VERSION_NUMBER_H


namespace xmilib {


//**********************************************************************************************************************
/// \brief Version number class
//**********************************************************************************************************************
class VersionNumber
{
public: // member functions
   VersionNumber(); ///< Default constructor.
   VersionNumber(qint32 major, qint32 minor); ///< Constructor.
   VersionNumber(VersionNumber const& other); ///< Copy-constructor.
   VersionNumber(VersionNumber&& other) noexcept; ///< Assignment copy-constructor.
   ~VersionNumber() = default; ///< Destructor.
   VersionNumber& operator=(VersionNumber const& other); ///< Assignment operator.
   VersionNumber& operator=(VersionNumber&& other) noexcept; ///< Move assignment operator.
   bool isValid() const; ///< Check if a version number is valid.
   bool operator==(VersionNumber const& other) const; ///< Equality test.
   bool operator!=(VersionNumber const& other) const; ///< Inequality test.
   bool operator<(VersionNumber const& other) const; ///< Strict inferiority test.
   bool operator<=(VersionNumber const& other) const; ///< Inferiority test.
   bool operator>(VersionNumber const& other) const; ///< Strict superiority test.
   bool operator>=(VersionNumber const& other) const; ///< Superiority test.
   void setValue(qint32 major, qint32 minor); ///< Set the version number.
   void setMajor(qint32 major); ///< Set the major version number.
   qint32 major() const; ///< Return the major version number.
   void setMinor(qint32 minor); ///< Set the minor version number.
   qint32 minor() const; ///< Return the minor version number.
   QString toString() const; ///< Return a string for the version number.
   static VersionNumber fromString(QString const& str); ///< Create a version number from a string.

private:
   qint32 major_; ///< The major version number.
   qint32 minor_; ///< The minor version number.
};


} // namespace xmilib




#endif // #ifndef XMILIB_VERSION_NUMBER_H
