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
void synthesizeKeyDown(quint32 virtualCode); ///< Synthesize a keyboard key press event
void synthesizeKeyUp(quint32 virtualCode); ///< Synthesize a keyboard key release event


}


#endif // #ifndef XMILIB__SYSTEM__UTILS__H