/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of system utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__SYSTEM__UTILS__H
#define XMILIB__SYSTEM__UTILS__H


namespace xmilib {



void displaySystemErrorDialog(QString const& title, QString const& message); ///< Display a system error message using the native GUI API.


#ifdef Q_OS_WIN


void synthesizeKeyDown(quint16 virtualCode); ///< Synthesize a keyboard key press event based on virtual key code
void synthesizeKeyUp(quint16 virtualCode); ///< Synthesize a keyboard key release event based on virtual key code
void synthesizeKeyDownAndUp(quint16 virtualCode); ///< Synthesize a keyboard key press then release event based on virtual key code
void synthesizeBackspaces(qint32 count); ///< Synthesize a series of backspace key press and releases
void synthesizeUnicodeKeyDown(quint16 unicodeChar); ///< Synthesize a keyboard key press event for a Unicode character
void synthesizeUnicodeKeyUp(quint16 unicodeChar); ///< Synthesize a keyboard key release event for a Unicode character
void synthesizeUnicodeKeyDownAndUp(quint16 unicodeChar); ///< Synthesize a keyboard key press then release event for a Unicode character


#endif // #ifdef Q_OS_WIN

}


#endif // #ifdef Q_OS_WIN
