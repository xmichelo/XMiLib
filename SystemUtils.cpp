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


//**********************************************************************************************************************
/// \param[in] virtualCode The virtual key code
/// \param[in] pressed Should the event be a key press or a key release
//**********************************************************************************************************************
void synthesizeKeystroke(quint32 virtualCode, bool pressed)
{
#ifdef WIN32
   INPUT input;
   input.type = INPUT_KEYBOARD;
   input.ki.wVk = virtualCode;
   input.ki.wScan = MapVirtualKey(virtualCode, MAPVK_VK_TO_VSC);
   input.ki.dwFlags = pressed ? 0 : KEYEVENTF_KEYUP;
   input.ki.time = 0;
   input.ki.dwExtraInfo = 0;
   SendInput(1, &input, sizeof(INPUT));
#else
#error This function is not supported on this platform
#endif   
}


} // namespace xmilib