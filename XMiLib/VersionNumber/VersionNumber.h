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
   VersionNumber(qint32 major, qint32 minor); ///< Default constructor.
   VersionNumber(VersionNumber const& other); ///< Copy-constructor.
   VersionNumber(VersionNumber&& other); ///< Assignment copy-constructor.
   ~VersionNumber() = default; ///< Destructor.
   VersionNumber& operator=(VersionNumber const& other); ///< Assignment operator.
   VersionNumber& operator=(VersionNumber&& other); ///< Move assignment operator.
   bool operator==(VersionNumber const& other) const; ///< Equality test.
   bool operator!=(VersionNumber const& other) const; ///< Inequality test.
   void setValue(qint32 major, qint32 minor); ///< Set the version number.
   void setMajor(qint32 major); ///< Set the major version number.
   qint32 major() const; ///< Return the major version number.
   void setMinor(qint32 minor); ///< Set the minor version number.
   qint32 minor() const; ///< Return the minor version number.
   QString toString() const; ///< Return a string for the version number.

private:
   quint32 major_; ///< The major version number.
   quint32 minor_; ///< The minor version number.
};


} // namespace xmilib




#endif // #ifndef XMILIB_VERSION_NUMBER_H
