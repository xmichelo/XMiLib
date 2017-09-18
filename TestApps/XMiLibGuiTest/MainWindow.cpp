/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "MainWindow.h"
#include <XMiLib/Exception.h>
#include <XMiLib/ThreadedOperation/ThreadedOperationDialog.h>


using namespace xmilib;


//**********************************************************************************************************************
/// \brief A dummy threaded operation
//**********************************************************************************************************************
class DummyThreadedOperation: public ThreadedOperation
{
public: // member functions
   DummyThreadedOperation(QObject* parent = nullptr): ThreadedOperation("Dummy operation", parent) {}  ///< Default constructor
	virtual ~DummyThreadedOperation() override = default; ///< Default destructor
   /// \brief run the operation
	virtual void run() override
   { 
      emit started();
      emit statusChanged("First Half.");
      for (qint32 i = 0; i <= 100; ++i)
      {
         this->thread()->msleep(30);
         if (50 == i)
            emit statusChanged("Second Half.");
         emit progress(i);
         if (this->isCanceled())
         {
            emit canceled();
            return;
         }
      }
      emit statusChanged("Done.");
      emit finished();
   }
   virtual bool isCancelable() const override { return true; }
private: // member functions
	DummyThreadedOperation(DummyThreadedOperation const&); ///< Disabled copy constructor
	DummyThreadedOperation& operator=(DummyThreadedOperation const&); ///< Disabled assignment operator
};


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui_()
   , styleSheetEditor_(nullptr)
   , debugLog_()
   , debugLogWindow_(nullptr)
{
   ui_.setupUi(this);
   debugLog_.enableLoggingToFile(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
      .absoluteFilePath("Log.txt"));
   styleSheetEditor_ = new StyleSheetEditor(this);
   styleSheetEditor_->setOriginalStyleSheet(qApp->styleSheet());
   styleSheetEditor_->loadStyleSheet();
}


//**********************************************************************************************************************
/// \param[in] type The type of log entry to add
/// \para,[in] message The message for the log entry
//**********************************************************************************************************************
void MainWindow::addDebugLogEntry(DebugLogEntry::EType type, QString const& message)
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
void MainWindow::onActionQuit()
{
   QApplication::closeAllWindows();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionShowStyleSheetEditor()
{
   styleSheetEditor_->show();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionShowDebugLog()
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
void MainWindow::onActionAddInfo()
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
void MainWindow::onActionAddWarning()
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
void MainWindow::onActionAddError()
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
void MainWindow::onActionOpenLogFile()
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
// 
//**********************************************************************************************************************
void MainWindow::onMaxEntryCountChange(int value)
{
   debugLog_.setMaxEntryCount(value);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionLaunchThreadWithoutDialog()
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   try
   {
      this->setEnabled(false);
      ThreadedOperation::runInEventLoop(DummyThreadedOperation());
      QMessageBox::information(this, tr("Info"), tr("The thread executed successfully."));
   }
   catch (xmilib::Exception const& e)
   {
   	QMessageBox::critical(this, tr("Error"), tr("The thread failed."));
   }
   this->setEnabled(true);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionLaunchThreadWithDialog()
{
   ThreadedOperationDialog::run(DummyThreadedOperation());
}


