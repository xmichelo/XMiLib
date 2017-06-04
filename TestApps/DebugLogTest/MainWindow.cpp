/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "MainWindow.h"
#include <XMiLib/Exception.h>


using namespace xmilib;


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
DebugLogTest::DebugLogTest(QWidget *parent)
   : QMainWindow(parent)
   , ui_()
   , debugLog_(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).absoluteFilePath("Log.txt"))
   , debugLogWindow_(nullptr)
{
    ui_.setupUi(this);
}


//**********************************************************************************************************************
/// \param[in] type The type of log entry to add
/// \para,[in] message The message for the log entry
//**********************************************************************************************************************
void DebugLogTest::addDebugLogEntry(DebugLogEntry::EType type, QString const& message)
{
   QString str(message.trimmed());
   switch (type)
   {
   case DebugLogEntry::Info:
      debugLog_.addInfo(str.isEmpty() ? "Info" : str);
      return;
   case DebugLogEntry::Warning:
      debugLog_.addWarning(str.isEmpty() ? "Warning" : str);
      return;
   case DebugLogEntry::Error:
      debugLog_.addError(str.isEmpty() ? "Error" : str);
      return;
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionShowDebugLog()
{
   try
   {
      if (!debugLogWindow_)
         debugLogWindow_ = new DebugLogWindow(&debugLog_, this);
      debugLogWindow_->show();
   }
   catch (xmilib::Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddInfo()
{
   try
   {
      this->addDebugLogEntry(DebugLogEntry::Info, ui_.editMessage->text());
   }
   catch (xmilib::Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddWarning()
{
   try
   {
      this->addDebugLogEntry(DebugLogEntry::Warning, ui_.editMessage->text());
   }
   catch (xmilib::Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddError()
{
   try
   {
      this->addDebugLogEntry(DebugLogEntry::Error, ui_.editMessage->text());
   }
   catch (xmilib::Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionOpenLogFile()
{
   try
   {
      QDesktopServices::openUrl(QUrl::fromLocalFile(debugLog_.getLogFilePath()));
   }
   catch (xmilib::Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());  	
   }
}


//**********************************************************************************************************************
/// \param[in] The new max entry count 
//**********************************************************************************************************************
void DebugLogTest::onMaxEntryCountChange(int value)
{
   debugLog_.setMaxEntryCount(value);
}


