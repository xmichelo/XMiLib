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
   explicit DummyThreadedOperation(QObject* parent = nullptr): ThreadedOperation("Dummy operation", parent) {}  ///< Default constructor
   ~DummyThreadedOperation() override = default; ///< Default destructor
   DummyThreadedOperation(DummyThreadedOperation const&) = delete; ///< Disabled copy constructor
   DummyThreadedOperation(DummyThreadedOperation&&) = delete; ///< Disabled move copy constructor
	DummyThreadedOperation& operator=(DummyThreadedOperation const&) = delete; ///< Disabled assignment operator
	DummyThreadedOperation& operator=(DummyThreadedOperation &&) = delete; ///< Disabled move assignment operator
   /// \brief run the operation
   void run() override
   { 
      emit started();
      emit statusChanged("First Half.");
      for (qint32 i = 0; i <= 100; ++i)
      {
         QThread::msleep(30);
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
   bool isCancelable() const override { return true; }
};


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui_()
   , debugLog_(std::make_shared<DebugLog>())
{
   ui_.setupUi(this);
   debugLog_->enableLoggingToFile(QDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation))
      .absoluteFilePath("Log.txt"));
   styleSheetEditor_ = new StyleSheetEditor(this);
   styleSheetEditor_->setOriginalStyleSheet(dynamic_cast<QApplication *>(QCoreApplication::instance())->styleSheet());
   // ReSharper disable once CppExpressionWithoutSideEffects
   styleSheetEditor_->loadStyleSheet();
}


//**********************************************************************************************************************
/// \param[in] type The type of log entry to add
/// \param[in] message The message for the log entry
//**********************************************************************************************************************
void MainWindow::addDebugLogEntry(DebugLogEntry::EType type, QString const& message) const
{
   QString const str(message.trimmed());
   switch (type)
   {
   case DebugLogEntry::Info:
      debugLog_->addInfo(str.isEmpty() ? "Info" : str);
      return;
   case DebugLogEntry::Warning:
      debugLog_->addWarning(str.isEmpty() ? "Warning" : str);
      return;
   case DebugLogEntry::Error:
      debugLog_->addError(str.isEmpty() ? "Error" : str);
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
void MainWindow::onActionShowStyleSheetEditor() const
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
         debugLogWindow_ = new DebugLogWindow(debugLog_, this);
      debugLogWindow_->show();
   }
   catch (Exception const& e)
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
   catch (Exception const& e)
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
   catch (Exception const& e)
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
   catch (Exception const& e)
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
      QDesktopServices::openUrl(QUrl::fromLocalFile(debugLog_->getLogFilePath()));
   }
   catch (Exception const& e)
   {
      QMessageBox::critical(this, tr("Error"), e.qwhat());
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onMaxEntryCountChange(int value) const
{
   if (debugLog_)
      debugLog_->setMaxEntryCount(value);
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
      DummyThreadedOperation op;
      ThreadedOperation::runInEventLoop(op);
      QMessageBox::information(this, tr("Info"), tr("The thread executed successfully."));
   }
   catch (Exception const&)
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
   DummyThreadedOperation op;
   ThreadedOperationDialog::run(op);
}


