/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of global shortcut manager
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__GLOBAL__SHORTCUT__MANAGER__H
#define XMILIB__GLOBAL__SHORTCUT__MANAGER__H


#include "GlobalShortcut.h"


namespace xmilib {


#ifdef _WIN32


//**********************************************************************************************************************
/// \brief Manager class for global (system wide) shortcuts
//**********************************************************************************************************************
class GlobalShortcutManager: public QAbstractNativeEventFilter
{
public: // static member functions
   static GlobalShortcutManager& instance(); ///< Return the only allowed instance of the class

public: // member functions
	~GlobalShortcutManager() = default; ///< Default destructor
   GlobalShortcut const* create(quint32 nativeModifiers, quint32 nativeVirtualKey, QString* outErrorMsg = nullptr); ///< Create a global shortcut
   bool remove(GlobalShortcut const* shortcut); ///< Remove (a.ka. delete) a global shortcut given its id
   bool nativeEventFilter(QByteArray const&, void* message, long*) override; ///< The Native event filter receiving thread event

private: // member functions
   GlobalShortcutManager(); ///< Default constructor
   GlobalShortcutManager(GlobalShortcutManager const&) = delete; ///< Disabled copy constructor
	GlobalShortcutManager(GlobalShortcutManager&&) = delete; ///< Disabled move constructor
	GlobalShortcutManager& operator=(GlobalShortcutManager const&) = delete; ///< Disabled assignment operator
	GlobalShortcutManager& operator=(GlobalShortcutManager&&) = delete; ///< Disabled move assignment operator

private: // data members
   std::list<UPGlobalShortcut> shortcuts_; ///< The list of active shortcuts
};


#endif // #ifdef _WIN32


} // namespace xmilib


#endif // #ifndef XMILIB__GLOBAL__SHORTCUT__MANAGER__H
