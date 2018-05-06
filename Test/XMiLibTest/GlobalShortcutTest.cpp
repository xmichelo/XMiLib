/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the xmilib::GlobalShortcut and xmilib::GlobalShortcutManager classes
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/GlobalShortcut/GlobalShortcutManager.h>


using namespace xmilib;


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::globalShortcut()
{
   try
   {
#ifdef Q_OS_WIN
      GlobalShortcutManager& gsm = GlobalShortcutManager::instance();
      quint32 const modifiers = MOD_CONTROL | MOD_ALT | MOD_SHIFT;
      quint32 const key = 'X';
      QString errMsg;
      GlobalShortcut const* shortcut = gsm.create(modifiers, key, &errMsg);
      QVERIFY2(shortcut, QString("Could not register the global shortcut: %1").arg(errMsg).toLocal8Bit());
      GlobalShortcut const* shortcutFail = gsm.create(modifiers, key, &errMsg);
      QVERIFY2(!shortcutFail, "Registration of an already bound shortcut should have failed but did not.");
      QVERIFY2(gsm.remove(shortcut), "Removal of an existing shortcut failed.");
      QVERIFY2(!gsm.remove(shortcut), "Removal of an already removed shortcut should have failed but did not.");
      QVERIFY2(!gsm.remove(shortcut + 8), "Removal of an non existing shortcut should have failed but did not.");
#endif // #ifdef Q_OS_WIN
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception.");
   }
}

