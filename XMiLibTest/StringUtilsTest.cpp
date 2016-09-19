/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the XMiLib string utility functions


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/StringUtils.h>


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::stringUtils_byteToHexString_data()
{
   QTest::addColumn<char>("byte");
   QTest::addColumn<QString>("expectedResult");
   QTest::newRow("0") << char(0) << QString("00");
   QTest::newRow("10") << char(10) << QString("0a");
   QTest::newRow("203") << char(203) << QString("cb");
   QTest::newRow("-1") << char(-1) << QString("ff");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::stringUtils_byteToHexString()
{
   QFETCH(char, byte);
   QFETCH(QString, expectedResult);
   QCOMPARE(xmilib::byteToHexString(byte), expectedResult);
}
