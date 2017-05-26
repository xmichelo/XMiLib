/// \file 
/// \author Xavier Michelon
/// 
/// \brief Implementation of custom exception class


#include "stdafx.h"
#include "Exception.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] what A description of the exception
//**********************************************************************************************************************
Exception::Exception(QString const& what) throw()
   : std::exception()
   , qWhat_(what)
   , cachedWhat_()
{

}


//**********************************************************************************************************************
/// \param[in] ref The Exception to copy from
//**********************************************************************************************************************
Exception::Exception(Exception const& ref) throw()
   : std::exception() 
   , qWhat_(ref.qWhat_)
   , cachedWhat_() // we do not copy cached what to save memory
{

}


//**********************************************************************************************************************
/// \return a C-style string describing the exception
//**********************************************************************************************************************
char const* Exception::what() const throw()
{
   if (0 == cachedWhat_.size())
      cachedWhat_ = qWhat_.toLatin1() + '\0'; // the final zero is added for safety, as constData() should add it automatically
   return cachedWhat_.constData();
}


//**********************************************************************************************************************
/// \return A Qt String describing the exception
//**********************************************************************************************************************
QString const& Exception::qwhat() const throw()
{
   return qWhat_;
}


} // namespace xmilib

