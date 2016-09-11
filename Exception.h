/// \file 
/// \date 2011-06-14
/// \author Xavier Michelon
/// 
/// \brief Declaration of custom exception class


#ifndef XMILIB__EXCEPTION__H
#define XMILIB__EXCEPTION__H


#include <stdexcept>


namespace xmilib {


//**********************************************************************************************************************
/// \brief Custom exception class
//**********************************************************************************************************************
class Exception: public std::exception
{
public: // member functions
   Exception(QString const&  what = QString()) throw(); ///< Constructor
   Exception(Exception const& ref) throw(); ///< copy constructor
   virtual ~Exception() throw(); ///< Destructor
   virtual char const* what() const throw() ; ///< Return the description of the exception as a C-style string
   virtual QString const& qwhat() const throw(); ///< Return the description of the exception as a QString

private: // member functions
   Exception& operator=(Exception const&) throw(); ///< Disabled assignment operator

private: // data members
   QString const what_; ///< The description of the exception
};


} // namespace xmilib


#endif // #ifndef XMILIB__EXCEPTION__H
 
