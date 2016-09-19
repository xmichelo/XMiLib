/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for the string utility functions in XMiLib


#include "stdafx.h"
#include "StringUtilsTest.h"
#include <XMiLib/StringUtils.h>



//**********************************************************************************************************************
// 
//**********************************************************************************************************************
StringUtilsTest::StringUtilsTest()
   : QObject()
{

}



//**********************************************************************************************************************
// 
//**********************************************************************************************************************
StringUtilsTest::~StringUtilsTest()
{

}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StringUtilsTest::byteToHexString_data()
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
void StringUtilsTest::byteToHexString()
{
   QFETCH(char, byte);
   QFETCH(QString, expectedResult);
   QCOMPARE(xmilib::byteToHexString(byte), expectedResult);
}
