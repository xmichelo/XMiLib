/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the XMiLib string utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/StringUtils.h>


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
// ReSharper disable once CppInconsistentNaming
void XMiLibTest::stringUtilsByteToHexString_data()
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
void XMiLibTest::stringUtilsByteToHexString()
{
   try
   {
      // ReSharper disable CppLocalVariableMayBeConst
      QFETCH(char, byte);
      QFETCH(QString, expectedResult);
      // ReSharper restore CppLocalVariableMayBeConst
      QCOMPARE(xmilib::byteToHexString(byte), expectedResult);
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
   
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
// ReSharper disable once CppInconsistentNaming
void XMiLibTest::stringUtilsByteArrayToHexString_data()
{
   QByteArray array;
   qint32 const arraySize(18);
   array.resize(arraySize);
   for (qint32 i = 0; i < arraySize; ++i)
      array[i] = i;
   QTest::addColumn<QByteArray>("array");
   QTest::addColumn<QString>("separator");
   QTest::addColumn<qint32>("bytesPerLine");
   QTest::addColumn<QString>("expectedResult");
   QTest::newRow("Empty array") << QByteArray() << QString() << 0 << QString();
   QTest::newRow("One byte array") << QByteArray(1, -1) << QString( ) << 2 << QString("ff");
   QTest::newRow("Compact array") << array << QString() << 0 << QString("000102030405060708090a0b0c0d0e0f1011");
   QTest::newRow("Space separated") << array << QString(" ") << -1 << 
      QString("00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11");
   QTest::newRow("Two characters separator") << array << QString("::") << 0 << 
      QString("00::01::02::03::04::05::06::07::08::09::0a::0b::0c::0d::0e::0f::10::11");
   QTest::newRow("Compact multiline") << array << QString() << 4 << 
      QString("00010203\n04050607\n08090a0b\n0c0d0e0f\n1011");
   QTest::newRow("Spaced multiline") << array << QString(" ") << 6 <<
      QString("00 01 02 03 04 05\n06 07 08 09 0a 0b\n0c 0d 0e 0f 10 11");
   QTest::newRow("Single column") << array << QString("-") << 1 << 
      QString("00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n0a\n0b\n0c\n0d\n0e\n0f\n10\n11");
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::stringUtilsByteArrayToHexString()
{
   try 
   {
      // ReSharper disable CppLocalVariableMayBeConst
      QFETCH(QByteArray, array);
      QFETCH(QString, separator);
      QFETCH(qint32, bytesPerLine);
      QFETCH(QString, expectedResult);
      // ReSharper restore CppLocalVariableMayBeConst
      QCOMPARE(xmilib::byteArrayToHexString(array, separator, bytesPerLine), expectedResult);
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
void XMiLibTest::stringUtilsBoolToString()
{
   try
   {
      QVERIFY2(xmilib::boolToString(false) == "false", R"(boolToString(false) did not return "false".)");
      QVERIFY2(xmilib::boolToString(true) == "true", R"(boolToString(true) did not return "true".)");
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception.");
   }
}


