/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of Qt application class that allows only a single instance
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "SingleInstanceApp.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] appKey The key identifying the application
//**********************************************************************************************************************
SingleInstanceApplication::SingleInstanceApplication(QString const& appKey)
   : sharedMem_(appKey)
{
   isFirstInstance_ = sharedMem_.create(sizeof(WId));
}


//**********************************************************************************************************************
/// \return true if no other instance of the application was running when this instance was created
//**********************************************************************************************************************
bool SingleInstanceApplication::isFirstInstance() const
{
   return isFirstInstance_;
}


}

