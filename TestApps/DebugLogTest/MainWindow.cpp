/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of main window class


#include "stdafx.h"
#include "MainWindow.h"


using namespace xmilib;


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
DebugLogTest::DebugLogTest(QWidget *parent)
   : QMainWindow(parent)
   , ui_()
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
   if (!debugLogWindow_)
      debugLogWindow_ = new DebugLogWindow(&debugLog_, this);
      debugLogWindow_->show();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddInfo()
{
   this->addDebugLogEntry(DebugLogEntry::Info, ui_.editMessage->text());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddWarning()
{
   this->addDebugLogEntry(DebugLogEntry::Warning, ui_.editMessage->text());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogTest::onActionAddError()
{
   this->addDebugLogEntry(DebugLogEntry::Error, ui_.editMessage->text());
}


