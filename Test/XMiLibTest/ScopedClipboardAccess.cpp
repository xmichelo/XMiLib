/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the xmilib::ScopedClipboardAccess class.
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/Scoped/ScopedClipboardAccess.h>


using namespace xmilib;


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::scopedClipboardAccess() {
    try {
        ScopedClipboardAccess const clipboard(nullptr);
        QVERIFY2(clipboard.isOpen(), "The clipboard could not be opened.");
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception.");
    }
}

