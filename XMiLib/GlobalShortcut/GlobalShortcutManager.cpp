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


#ifdef Q_OS_WIN


//****************************************************************************************************************************************************
/// \return The only allowed instance of the class
//****************************************************************************************************************************************************
GlobalShortcutManager &GlobalShortcutManager::instance() {
    static GlobalShortcutManager instance;
    return instance;
}


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
GlobalShortcutManager::GlobalShortcutManager() {
    // we register this class to be notified of Windows message posted for this application
    QCoreApplication::instance()->installNativeEventFilter(this);
}


//****************************************************************************************************************************************************
/// \param[in] nativeModifiers A bitfield containing the modifiers for the short (available values are MOD_SHIFT, 
/// MOD_ALT, MOD_CONTROL and MOD_WIN)
/// \param[in] nativeVirtualKey The virtual key for the shortcut
/// \param[out] outErrorMsg if the function returns null and this variable is not null, a description of the error
/// is placed in the variable pointed by outErrorMsg
/// \return A non-null pointer to the shortcut. The shortcut owned by the manager and must not be deleted manually.
/// To 'delete' a shortcut use GlobalShortcutManager::remove() instead
/// \return A null pointer if the registration failed
//****************************************************************************************************************************************************
GlobalShortcut const *GlobalShortcutManager::create(quint32 nativeModifiers, quint32 nativeVirtualKey,
    QString *outErrorMsg) {
    try {
        UpGlobalShortcut shortcut = std::make_unique<GlobalShortcut>(nativeModifiers, nativeVirtualKey);
        GlobalShortcut const *result = shortcut.get();
        shortcuts_.push_back(std::move(shortcut));
        return result;
    }
    catch (Exception const &e) {
        if (outErrorMsg)
            *outErrorMsg = e.qwhat();
        return nullptr;
    }
}


//****************************************************************************************************************************************************
/// \return true if and only if the function was successful
//****************************************************************************************************************************************************
bool GlobalShortcutManager::remove(GlobalShortcut const *shortcut) {
    std::list<UpGlobalShortcut>::iterator const it = std::find_if(shortcuts_.begin(), shortcuts_.end(), [&shortcut](UpGlobalShortcut const &sc) -> bool { return sc.get() == shortcut; });
    if (shortcuts_.end() == it)
        return false;
    shortcuts_.erase(it);
    return true;
}


//****************************************************************************************************************************************************
/// \param[in] message The message
/// \return true if the message has been processed
//****************************************************************************************************************************************************
bool GlobalShortcutManager::nativeEventFilter(QByteArray const &, void *message, qintptr *) {
    MSG const *msg = static_cast<MSG *>(message);
    if (WM_HOTKEY == msg->message) {
        WPARAM const id = msg->wParam;
        std::list<UpGlobalShortcut>::iterator const it = std::find_if(shortcuts_.begin(), shortcuts_.end(), [&id](UpGlobalShortcut const &sc) -> bool { return sc->id_ == id; });
        if (shortcuts_.end() == it)
            return false;
        (*it)->trigger();
        return true;
    }
    // The documentation for WM_HOTKEY does not state anything about the result so we leave it untouched
    return false;
}


//****************************************************************************************************************************************************
//
//****************************************************************************************************************************************************
void GlobalShortcutManager::reset() {
    shortcuts_.clear();
}


#endif // #ifdef Q_OS_WIN


} // namespace xmilib
