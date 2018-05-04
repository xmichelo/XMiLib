/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of global shortcut class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "GlobalShortcut.h"
#include "Exception.h"


namespace xmilib {


#ifdef _WIN32


//**********************************************************************************************************************
/// This function will throw a xmilib::Exception if the shortcut cannot be registered
///
/// \param[in] nativeModifiers A bitfield containing the modifiers for the short (available values are MOD_SHIFT, 
/// MOD_ALT, MOD_CONTROL and MOD_WIN)
/// \param[in] nativeVirtualKey The virtual key for the shortcut
//**********************************************************************************************************************
GlobalShortcut::GlobalShortcut(quint32  nativeModifiers, quint32 nativeVirtualKey)
   : QObject(nullptr)
   , id_(GlobalAddAtom(QUuid::createUuid().toString().toStdWString().c_str()))
{
   if (!id_)
      throw Exception("Could not obtain an ID for the global shortcut to trigger combos.");
   if (!RegisterHotKey(nullptr, id_, nativeModifiers | MOD_NOREPEAT, nativeVirtualKey))
      throw Exception("Could not register global shortcut for combos.");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void GlobalShortcut::trigger()
{
   emit triggered();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GlobalShortcut::~GlobalShortcut()
{
   UnregisterHotKey(nullptr, id_);
   GlobalDeleteAtom(id_);
}


#endif // #ifdef _WIN32


} // namespace xmilib
