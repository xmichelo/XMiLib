/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the xmilib::ScopedGlobalMemoryLock class.
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/Scoped/ScopedGlobalMemoryLock.h>


using namespace xmilib;


namespace {


QString const kTestString = "Test String"; ///< A test string.


}


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::scopedGlobalMemoryLock() {
    try {
        QByteArray const origArray = kTestString.toLocal8Bit();
        qint32 const size = origArray.size();
        HGLOBAL const handle = GlobalAlloc(GMEM_MOVEABLE, origArray.size());

        // Allocate global memory.
        QVERIFY2(handle, "GlobalAlloc() failed.");

        {
            // Lock the global memory and write to it.
            ScopedGlobalMemoryLock const memLock(handle);
            quint32 *pointer = reinterpret_cast<quint32 *>(memLock.pointer());
            QVERIFY2(memLock.locked() && pointer, "The scoped global memory locked failed.");
            memcpy(pointer, origArray.constData(), size);
        }

        {
            // Lock the global memory again, read back and verify it matches what was written.
            ScopedGlobalMemoryLock const memLock(handle);
            quint32 *pointer = reinterpret_cast<quint32 *>(memLock.pointer());
            QVERIFY2(memLock.locked() && pointer, "The scoped global memory locked failed.");

            QByteArray finalArray(size, 0);
            memcpy(finalArray.data(), pointer, size);
            QVERIFY2(finalArray == origArray, "Readback failed.");
        }

        // Free the global memory
        QVERIFY2(!GlobalFree(handle), "GlobalFree() failed.");
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception.");
    }
}

