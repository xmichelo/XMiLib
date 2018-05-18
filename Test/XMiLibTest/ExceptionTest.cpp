/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the xmilib::Exception class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/Exception.h>


namespace {
   QString const kExceptionMessage("xmilib::Exception"); ///< The message used for testing exception
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::exceptionHandling()
{
   qint32 exitPoint = 0;
   try 
   {
      throw xmilib::Exception();
   }
   catch (xmilib::Exception const&)
   {
      exitPoint = 2;
   }
   QCOMPARE(exitPoint, 2);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
// ReSharper disable once CppInconsistentNaming
void XMiLibTest::exceptionMessage_data()
{
   QTest::addColumn<QString>("message");
   QTest::newRow("Non empty exception message") << kExceptionMessage;
   QTest::newRow("Empty exception message") << QString("");
   QTest::newRow("Null exception message") << QString();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::exceptionMessage()
{
   try
   {
      QString whatStr("foo");
      QString qWhatStr("bar");
      // ReSharper disable CppLocalVariableMayBeConst
      QFETCH(QString, message);
      // ReSharper restore CppLocalVariableMayBeConst
      try 
      {
         throw xmilib::Exception(message);
      }
      catch (xmilib::Exception const& e)
      {
         whatStr = QString::fromLatin1(e.what());
         qWhatStr = e.qwhat();
      }
      QCOMPARE(whatStr, message);
      QCOMPARE(qWhatStr, message);
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}

