/// \file 
/// \date 2011-06-14
/// \author Xavier Michelon
/// 
/// \brief Declaration of custom exception class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_EXCEPTION_H
#define XMILIB_EXCEPTION_H


namespace xmilib {


//**********************************************************************************************************************
/// \brief Custom exception class
//**********************************************************************************************************************
class Exception: public std::exception
{
public: // member functions
   Exception(QString const&  what = QString()) noexcept; ///< Constructor
   Exception(Exception const& ref) noexcept; ///< copy constructor
   Exception(Exception&& ref) noexcept; ///< copy constructor
   Exception& operator=(Exception const&) = delete; ///< Disabled assignment operator
   Exception& operator=(Exception&&) = delete; ///< Disabled assignment operator
   virtual ~Exception() noexcept = default; ///< Destructor
   virtual char const* what() const noexcept override; ///< Return the description of the exception as a C-style string
   virtual QString const& qwhat() const noexcept; ///< Return the description of the exception as a QString

private: // data members
   QString const qWhat_; ///< The description of the exception
   mutable QByteArray cachedWhat_; ///< The byte array containing the description of the exception as an ASCII latin1 char array. To save memory the content of this variable is only valid after what has been called once
};


} // namespace xmilib


#endif // #ifndef XMILIB_EXCEPTION_H
