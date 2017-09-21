/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of system utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "SystemUtils.h"


namespace xmilib {


//**********************************************************************************************************************
/// This function is intended to be called when the Qt GUI is not available, for instance in a top level exception 
/// handler.
///
/// \param[in] title The title for the dialog
/// \param[in] message The message
//**********************************************************************************************************************
void displaySystemErrorDialog(QString const& title, QString const& message)
{
#ifdef WIN32
   MessageBox(nullptr, LPCWSTR(message.utf16()), LPCWSTR(title.utf16()), MB_OK | MB_ICONERROR);
#else
#error This function is not supported on this platform
#endif
   qDebug() << QString("Unhandled exception: %1").arg(message);
}


} // namespace xmilib