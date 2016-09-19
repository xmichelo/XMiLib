/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for xmilib::Exception


#include "stdafx.h"
#include "ExceptionTest.h"
#include <XMiLib/Exception.h>


namespace {
   QString const kExceptionMessage("xmilib::Exception"); ///< The message used for testing exception
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ExceptionTest::exceptionHandling()
{
   qint32 exitPoint = 0;
   try 
   {
      throw xmilib::Exception();
      exitPoint = 1;
   }
   catch (xmilib::Exception const& e)
   {
      exitPoint = 2;
   }
   QCOMPARE(exitPoint, 2);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ExceptionTest::exceptionMessage_data()
{
   QTest::addColumn<QString>("message");
   QTest::newRow("Non empty exception message") << kExceptionMessage;
   QTest::newRow("Empty exception message") << QString("");
   QTest::newRow("Null exception message") << QString();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ExceptionTest::exceptionMessage()
{
   QString whatStr("foo");
   QString qWhatStr("bar");
   QFETCH(QString, message);
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

