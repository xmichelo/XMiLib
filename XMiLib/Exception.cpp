/// \file 
/// \author Xavier Michelon
/// 
/// \brief Implementation of custom exception class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "Exception.h"
#include <utility>


namespace xmilib {


//****************************************************************************************************************************************************
/// \param[in] what A description of the exception
//****************************************************************************************************************************************************
Exception::Exception(QString what) noexcept
    : qWhat_(std::move(what)) {
}


//****************************************************************************************************************************************************
/// \param[in] ref The Exception to copy from
//****************************************************************************************************************************************************
Exception::Exception(Exception const &ref) noexcept
    : std::exception(ref), qWhat_(ref.qWhat_)
// we do not copy cached what to save memory
{
}


//****************************************************************************************************************************************************
/// \param[in] ref The Exception to copy from
//****************************************************************************************************************************************************
Exception::Exception(Exception &&ref) noexcept
    : std::exception(ref), qWhat_(ref.qWhat_) {
}


//****************************************************************************************************************************************************
/// \return a C-style string describing the exception
//****************************************************************************************************************************************************
char const *Exception::what() const noexcept {
    if (0 == cachedWhat_.size())
        cachedWhat_ = qWhat_.toLatin1() + '\0';
    // the final zero is added for safety, as constData() should add it automatically
    return cachedWhat_.constData();
}


//****************************************************************************************************************************************************
/// \return A Qt String describing the exception
//****************************************************************************************************************************************************
QString const &Exception::qwhat() const noexcept {
    return qWhat_;
}


} // namespace xmilib
