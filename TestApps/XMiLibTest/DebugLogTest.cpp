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
      for (int i = 0; i < 998; ++i)
         log.addError(kErrorMessage);
      QVERIFY2(1000 == log.size(), "The size of a log with 1000 items is not 1000");
      log.setMaxEntryCount(500);
      QVERIFY2(500 == log.getMaxEntryCount(), "log.getMaxEntryCount() returns an invalid value");
      QVERIFY2(500 == log.size(), "Setting max log entry count does not resize properly");
      log.setMaxEntryCount(600);
      QVERIFY2(500 == log.size(), "Expanding max log entry count should not modify current item count");
      for (qint32 i = 0; i < 200; ++i)
         log.addInfo(kInfoMessage);
      QVERIFY2(600 == log.size(), "Limiting entry count does not work");
      log.setMaxEntryCount(1);
      QVERIFY2(1 == log.size(), "Setting max log entry count does not resize properly");
      log.setMaxEntryCount(0);
      QVERIFY2(0 == log.getMaxEntryCount(), "log.getMaxEntryCount() returns an invalid value");
      for (qint32 i = 1; i < 1000; ++i)
         log.addInfo(kInfoMessage);
      QVERIFY2(1000 == log.size(), "Returning to unlimited entry count does not work");
      bool didThrow = false;
      try { log.setMaxEntryCount(-1); } catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(didThrow, "Setting the max entry count to a negative value should throw an exception");
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
      try { SPDebugLogEntry logEntry = log[-1]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(didThrow, "operator [] did not throw with negative index");
      didThrow = false;
      try { SPDebugLogEntry logEntry = log[3]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(didThrow, "operator [] did not throw with an out of range index");
      didThrow = false;
      try { SPDebugLogEntry logEntry = log[2]; }
      catch (xmilib::Exception const& e) { didThrow = true; }
      QVERIFY2(!didThrow, "operator [] threw an exception for an valid index");
      SPDebugLogEntry entry = log[0];
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


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::debugLog_tableModel()
{
   try
   {
      DebugLog log;
      QVERIFY2(2 == log.columnCount(), "The number of column in the table model is invalid");
      QVERIFY2(0 == log.rowCount(), "The number of row in the empty table model is invalid");
      log.addInfo(kInfoMessage);
      log.addWarning(kWarningMessage);
      log.addError(kErrorMessage);
      QVERIFY2(2 == log.columnCount(), "The number of column in the table model is invalid");
      QVERIFY2(3 == log.rowCount(), "The number of row in the table model is invalid");
      for (qint32 i = 0; i < 3; ++i)
      {
         QVERIFY2(log.data(log.index(i, 0), Qt::DisplayRole).toString() == log[i]->getDateTime()
            .toString("yyyy-MM-dd HH:mm:ss.zzz"), 
            QString("Data for display role of column 0 and row %1 is invalid").arg(i).toLocal8Bit());
         QVERIFY2(log.data(log.index(i, 1), Qt::DisplayRole).toString() == log[i]->getMessage(),
            QString("Data for display role of column 1 and row %1 is invalid").arg(i).toLocal8Bit());
      }
   }
   catch (...)
   {
   	QVERIFY2(false, "the function threw an exception");
   }
}

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::debugLog_file()
{
   try
   {
      DebugLog log;
      QVERIFY2(!log.isLoggingToFileEnabled(), "isLoggingToFile() should return false on a newly created log");
      QString const logFilePath = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation))
         .absoluteFilePath(QTime::currentTime().toString("hhmmsszzz_Log.txt"));
      QVERIFY2(log.enableLoggingToFile(logFilePath), "Creation of log file failed");
      QVERIFY2(log.isLoggingToFileEnabled(), "isLoggingToFile() should return true after specifying a valid log file");
      log.disableLoggingToFile();
      QVERIFY2(!log.isLoggingToFileEnabled(), "isLoggingToFile() should return false after disabling logging to file");
      QVERIFY2(!log.enableLoggingToFile("C:/wefwefewlkjfewvoiewnvoewvne/vjfmvg/ewjflkewjfnewf.kiewjfowefewfewfw"), 
         "enableLoggingToFile() should return false after specifying an impossible log file path");
      QFile(logFilePath).remove();

   }
   catch (...)
   {
   	QVERIFY2(false, "the function threw an exception");
   }
}


