/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of global shortcut manager
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "GlobalShortcutManager.h"
#include "Exception.h"



namespace xmilib {


#if defined(_WIN32) || defined(Win32)


//**********************************************************************************************************************
/// \return The only allowed instance of the class
//**********************************************************************************************************************
GlobalShortcutManager& GlobalShortcutManager::instance()
{
   static GlobalShortcutManager instance;
   return instance;
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
GlobalShortcutManager::GlobalShortcutManager()
{
   // we register this class to be notified of Windows message posted for this application
   qApp->installNativeEventFilter(this);
}


//**********************************************************************************************************************
/// \param[in] nativeModifiers A bitfield containing the modifiers for the short (available values are MOD_SHIFT, 
/// MOD_ALT, MOD_CONTROL and MOD_WIN)
/// \param[in] nativeVirtualKey The virtual key for the shortcut
/// \param[out] outErrorMsg if the function returns null and this variable is not null, a description of the error
/// is placed in the variable pointed by outErrorMsg
/// \return A non-null pointer to the shortcut. The shortcut owned by the manager and must not be deleted manually.
/// To 'delete' a shortcut use GlobalShortcutManager::remove() instead
/// \return A null pointer if the registration failed
//**********************************************************************************************************************
GlobalShortcut const* GlobalShortcutManager::create(quint32  nativeModifiers, quint32 nativeVirtualKey, 
   QString* outErrorMsg)
{
   try
   {
      UPGlobalShortcut shortcut = UPGlobalShortcut(new GlobalShortcut(nativeModifiers, nativeVirtualKey));
      GlobalShortcut* result = shortcut.get();
      shortcuts_.push_back(std::move(shortcut));
      return result;
   }
   catch (xmilib::Exception const& e)
   {
      if (outErrorMsg)
         *outErrorMsg = e.qwhat();
      return nullptr;
   }
}


//**********************************************************************************************************************
/// \return true if and only if the function was successful
//**********************************************************************************************************************
bool GlobalShortcutManager::remove(GlobalShortcut const* shortcut)
{
   std::list<UPGlobalShortcut>::iterator const it = std::find_if(shortcuts_.begin(), shortcuts_.end(),
      [&shortcut](UPGlobalShortcut const& sc) -> bool { return sc.get() == shortcut; });
   if (shortcuts_.end() == it)
      return false;
   shortcuts_.erase(it);
   return true;
}


//**********************************************************************************************************************
/// \param[in] message The message
/// \return true if the message has been processed
//**********************************************************************************************************************
bool GlobalShortcutManager::nativeEventFilter(QByteArray const&, void* message, long*)
{
   MSG* msg = static_cast<MSG*>(message);
   if (WM_HOTKEY == msg->message)
   {
      quint32 const id = msg->wParam;
      std::list<UPGlobalShortcut>::iterator const it = std::find_if(shortcuts_.begin(), shortcuts_.end(),
         [&id](UPGlobalShortcut const& sc) -> bool { return sc->id_ == id; });
      if (shortcuts_.end() == it)
         return false;
      (*it)->trigger();
      return true;
   }
   // The documentation for WM_HOTKEY does not state anything about the result so we leave it untouched
   return false;
}


#endif // #if defined(_WIN32) || defined(Win32)


} // namespace xmilib
