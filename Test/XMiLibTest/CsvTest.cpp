/// \file
/// \author 
///
/// \brief Implementation of CSV unit tests.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/File/FileUtils.h>
#include <XMiLib/File/CsvIO.h>


namespace {


QVector<QStringList> const kSampleData = {
    { "1997", "Ford",  "E350",                                     "ac, abs, moon",                      "3000.00" },
    { "1999", "Chevy", "Venture \"Extended Edition\"",             "",                                   "4900.00" },
    { "1999", "Chevy", "Venture \"Extended Edition, Very Large\"", "",                                   "5000.00" },
    { "1996", "Jeep",  "Grand Cherokee",                           "MUST SELL!\nair, moon roof, loaded", "4799.00" }
};


}


using namespace xmilib;


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::csvIo() {
    try {
        QVector<QStringList> result;
        QString const filePath = getTempFilePath();
        QString errMsg;
        bool ok = loadCsvFile(filePath, result);
        QVERIFY2(!ok, "The function should have failed.");
        ok = saveCsvFile(filePath, kSampleData, &errMsg);
        QVERIFY2(ok, QString("Saving of the CSV file failed. %1").arg(errMsg).toLocal8Bit());
        ok = loadCsvFile(filePath, result, &errMsg);
        QVERIFY2(ok, QString("Loading of the CSV file failed. %1").arg(errMsg).toLocal8Bit());
        QVERIFY2(result == kSampleData, "The loaded CSV content is not equal to the saved data.");
        QVector<QStringList> badData = kSampleData;
        badData[2].pop_back();
        ok = saveCsvFile(filePath, badData, &errMsg);
        QVERIFY2(ok, QString("Saving of the bad CSV file failed. %1").arg(errMsg).toLocal8Bit());
        ok = loadCsvFile(filePath, badData);
        QVERIFY2(!ok, "Loading an invalid CSV file should have failed.");
        QFile(filePath).remove();
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception.");
    }
}
