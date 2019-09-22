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


#ifdef Q_OS_WIN


void synthesizeKeyEvent(quint16 virtualCode, bool pressed); ///< Synthesize a key event based on a virtual key code
void synthesizeUnicodeKeyEvent(quint16 unicodeChar, bool pressed); ///< Synthesize a key event for a unicode character


#endif // #ifdef Q_OS_WIN


//**********************************************************************************************************************
/// This function is intended to be called when the Qt GUI is not available, for instance in a top level exception 
/// handler.
///
/// \param[in] title The title for the dialog
/// \param[in] message The message
//**********************************************************************************************************************
void displaySystemErrorDialog(QString const& title, QString const& message)
{
#ifdef Q_OS_WIN
   MessageBox(nullptr, LPCWSTR(message.utf16()), LPCWSTR(title.utf16()), MB_OK | MB_ICONERROR);
#endif
   (void)title; // does nothing but avoid 'unused parameter warning on some compilers
   qDebug() << QString("Unhandled exception: %1").arg(message);
}


#ifdef Q_OS_WIN


//**********************************************************************************************************************
/// \param[in] virtualCode The virtual key code
/// \param[in] pressed Should the event be a key press or a key release
//**********************************************************************************************************************
void synthesizeKeyEvent(quint16 virtualCode, bool pressed)
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


//**********************************************************************************************************************
/// \param[in] virtualCode The virtual key code
//**********************************************************************************************************************
void synthesizeKeyDown(quint16 virtualCode)
{
   synthesizeKeyEvent(virtualCode, true);
}


//**********************************************************************************************************************
/// \param[in] virtualCode The virtual key code
//**********************************************************************************************************************
void synthesizeKeyUp(quint16 virtualCode)
{
   synthesizeKeyEvent(virtualCode, false);
}


//**********************************************************************************************************************
/// \param[in] virtualCode The virtual key code
//**********************************************************************************************************************
void synthesizeKeyDownAndUp(quint16 virtualCode)
{
#ifdef WIN32
   INPUT sampleInput;
   sampleInput.type = INPUT_KEYBOARD;
   sampleInput.ki.wVk = virtualCode;
   sampleInput.ki.wScan = MapVirtualKey(virtualCode, MAPVK_VK_TO_VSC);
   sampleInput.ki.dwFlags = 0;
   sampleInput.ki.time = 0;
   sampleInput.ki.dwExtraInfo = 0;
   
   std::vector<INPUT> input(2, sampleInput);
   input[1].ki.dwFlags = KEYEVENTF_KEYUP;
   SendInput(2, input.data(), sizeof(INPUT));
#else
#error This function is not supported on this platform
#endif 
}


//**********************************************************************************************************************
/// \param[in] count The number of backspace to synthesize. if count is 0 or less, the function does nothing
//**********************************************************************************************************************
void synthesizeBackspaces(qint32 count)
{
#ifdef WIN32
   if (count < 1)
      return;

   INPUT sampleInput;
   sampleInput.type = INPUT_KEYBOARD;
   sampleInput.ki.wVk = VK_BACK;
   sampleInput.ki.wScan = MapVirtualKey(VK_BACK, MAPVK_VK_TO_VSC);
   sampleInput.ki.dwFlags = 0;
   sampleInput.ki.time = 0;
   sampleInput.ki.dwExtraInfo = 0;

   std::vector<INPUT> input(count * 2, sampleInput);
   for (int i = 1; i < count * 2; i += 2)
      input[i].ki.dwFlags = KEYEVENTF_KEYUP;
   SendInput(count * 2, input.data(), sizeof(INPUT));
#else
#error This function is not supported on this platform
#endif 
}





//**********************************************************************************************************************
/// \param[in] unicodeChar The Unicode character to synthesize
/// \param[in] pressed Should the event be a key press or a key release
//**********************************************************************************************************************
void synthesizeUnicodeKeyEvent(quint16 unicodeChar, bool pressed)
{
#ifdef WIN32
   INPUT input;
   input.type = INPUT_KEYBOARD;
   input.ki.wVk = 0;
   input.ki.wScan = unicodeChar;
   input.ki.dwFlags = (pressed ? 0 : KEYEVENTF_KEYUP) | KEYEVENTF_UNICODE;
   input.ki.time = 0;
   input.ki.dwExtraInfo = 0;
   SendInput(1, &input, sizeof(INPUT));
#else
#error This function is not supported on this platform
#endif   
}


//**********************************************************************************************************************
/// \param[in] unicodeChar The unicode char to synthesize
//**********************************************************************************************************************
void synthesizeUnicodeKeyDown(quint16 unicodeChar)
{
   synthesizeUnicodeKeyEvent(unicodeChar, true);
}


//**********************************************************************************************************************
/// \param[in] unicodeChar The unicode char to synthesize
//**********************************************************************************************************************
void synthesizeUnicodeKeyUp(quint16 unicodeChar)
{
   synthesizeUnicodeKeyEvent(unicodeChar, false);
}


//**********************************************************************************************************************
/// \param[in] unicodeChar The unicode char to synthesize
//**********************************************************************************************************************
void synthesizeUnicodeKeyDownAndUp(quint16 unicodeChar)
{
#ifdef WIN32
   INPUT sampleInput;
   sampleInput.type = INPUT_KEYBOARD;
   sampleInput.ki.wVk = 0;
   sampleInput.ki.wScan = unicodeChar;
   sampleInput.ki.dwFlags = KEYEVENTF_UNICODE;
   sampleInput.ki.time = 0;
   sampleInput.ki.dwExtraInfo = 0;
   
   std::vector<INPUT> input(2, sampleInput);
   input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_KEYUP;
   SendInput(2, input.data(), sizeof(INPUT));
#else
#error This function is not supported on this platform
#endif   
}


#endif // #ifdef Q_OS_WIN


} // namespace xmilib
