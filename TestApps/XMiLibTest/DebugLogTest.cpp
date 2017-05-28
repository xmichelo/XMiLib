/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the xmilib::DebugLog class


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/DebugLog/DebugLog.h>
#include <XMiLib/Exception.h>


using namespace xmilib;


namespace {
   QString kInfoMessage("Info"); ///< Sample info message
   QString kWarningMessage("Warning"); ///< Sample warning message
   QString kErrorMessage("Error"); ///< Sample warning message
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::debugLog_size()
{
   try
   {
      DebugLog log;
      QVERIFY2(0 == log.size(), "The size of an empty log is not zero");
      log.addInfo(kInfoMessage);
      QVERIFY2(1 == log.size(), "The size of a log with one item is not one");
      log.addWarning(kWarningMessage);
      QVERIFY2(2 == log.size(), "The size of a log with two items is not two");
      for (int i = 1; i <= 998; ++i)
         log.addError(kErrorMessage);
      QVERIFY2(1000 == log.size(), "The size of a log with 1000 items is not 1000");
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::debugLog_contents()
{
   try
   {
      DebugLog log;
      log.addInfo(kInfoMessage);
      log.addWarning(kWarningMessage);
      log.addError(kErrorMessage);
      bool didThrow(false);
      try { SPLogEntry logEntry = log[-1]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(didThrow, "operator [] did not throw with negative index");
      didThrow = false;
      try { SPLogEntry logEntry = log[3]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(didThrow, "operator [] did not throw with an out of range index");
      didThrow = false;
      try { SPLogEntry logEntry = log[2]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(!didThrow, "operator [] threw an exception for an valid index");
      SPLogEntry entry = log[0];
      QString const invalidContents("The contents in invalid");
      char const* cInvalidContents = invalidContents.toLocal8Bit().constData();
      QVERIFY2(DebugLogEntry::Info == log[0]->getType(), cInvalidContents);
      QVERIFY2(kInfoMessage == log[0]->getMessage(), cInvalidContents);
      QVERIFY2(DebugLogEntry::Warning == log[1]->getType(), cInvalidContents);
      QVERIFY2(kWarningMessage == log[1]->getMessage(), cInvalidContents);
      QVERIFY2(DebugLogEntry::Error == log[2]->getType(), cInvalidContents);
      QVERIFY2(kErrorMessage == log[2]->getMessage(), cInvalidContents);
      QDateTime const now(QDateTime::currentDateTime());
      QVERIFY2(log[0]->getDateTime() <= log[1]->getDateTime(), cInvalidContents);
      QVERIFY2(log[1]->getDateTime() <= log[2]->getDateTime(), cInvalidContents);
      for (qint32 i = 0; i < 3; i++)
         QVERIFY2(qAbs<qint64>(log[i]->getDateTime().secsTo(now)) < 1, cInvalidContents);
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}
