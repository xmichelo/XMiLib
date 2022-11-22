/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of global shortcut class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_GLOBAL_SHORTCUT_H
#define XMILIB_GLOBAL_SHORTCUT_H


#include <memory>


namespace xmilib {


//****************************************************************************************************************************************************
/// \brief A class for global (system-wide) shortcuts
/// 
/// Global shortcuts cannot be instanciated directly. The must be created using GlobalShortcutManager
//****************************************************************************************************************************************************
class GlobalShortcut : public QObject {
Q_OBJECT
public: // member functions
    GlobalShortcut(quint32 nativeModifiers, quint32 nativeVirtualKey); ///< constructor
    ~GlobalShortcut() override; ///< Default destructor
    GlobalShortcut(GlobalShortcut const &) = delete; ///< Disabled copy constructor
    GlobalShortcut(GlobalShortcut &&) = delete; ///< Disabled move constructor
    GlobalShortcut &operator=(GlobalShortcut const &) = delete; ///< Disabled assignment operator
    GlobalShortcut &operator=(GlobalShortcut &&) = delete; ///< Disabled move assignment operator

signals :
    void triggered(); ///< Signal emitted when the shortcut has been triggered

private: // member functions
    void trigger(); ///< trigger the shortcut

private:
    quint32 const id_; ///< The ID for the shortcut

    friend class GlobalShortcutManager;
};


typedef std::unique_ptr<GlobalShortcut> UpGlobalShortcut; ///< Type definition for unique pointer to global shortcut


} // namespace xmilib


#endif // #ifndef XMILIB_GLOBAL_SHORTCUT_H
