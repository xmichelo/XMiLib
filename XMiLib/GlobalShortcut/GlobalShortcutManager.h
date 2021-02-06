/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of global shortcut manager
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_GLOBAL_SHORTCUT_MANAGER_H
#define XMILIB_GLOBAL_SHORTCUT_MANAGER_H


#include "GlobalShortcut.h"


namespace xmilib {


#ifdef Q_OS_WIN


//**********************************************************************************************************************
/// \brief Manager class for global (system wide) shortcuts
//**********************************************************************************************************************
class GlobalShortcutManager: public QAbstractNativeEventFilter
{
public: // static member functions
   static GlobalShortcutManager& instance(); ///< Return the only allowed instance of the class

public: // member functions
   GlobalShortcutManager(GlobalShortcutManager const&) = delete; ///< Disabled copy constructor
	GlobalShortcutManager(GlobalShortcutManager&&) = delete; ///< Disabled move constructor
	~GlobalShortcutManager() override = default; ///< Default destructor
	GlobalShortcutManager& operator=(GlobalShortcutManager const&) = delete; ///< Disabled assignment operator
	GlobalShortcutManager& operator=(GlobalShortcutManager&&) = delete; ///< Disabled move assignment operator
   GlobalShortcut const* create(quint32 nativeModifiers, quint32 nativeVirtualKey, QString* outErrorMsg = nullptr); ///< Create a global shortcut
   bool remove(GlobalShortcut const* shortcut); ///< Remove (a.ka. delete) a global shortcut given its id
   bool nativeEventFilter(QByteArray const&, void* message, qintptr*) override; ///< The Native event filter receiving thread event

private: // member functions
   GlobalShortcutManager(); ///< Default constructor

private: // data members
   std::list<UpGlobalShortcut> shortcuts_; ///< The list of active shortcuts
};


#endif // #ifdef Q_OS_WIN


} // namespace xmilib


#endif // #ifndef XMILIB_GLOBAL_SHORTCUT_MANAGER_H
