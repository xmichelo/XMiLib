/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of threaded operation dialog
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "ThreadedOperationDialog.h"
#include "ui_ThreadedOperationDialog.h"
#include "Exception.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] operation The operation
/// \param[in] parent The parent widget of the dialog
/// \return true if and only if the operation completed successfully
//**********************************************************************************************************************
bool ThreadedOperationDialog::run(ThreadedOperation& operation, QWidget* parent)
{
   return QDialog::Accepted == ThreadedOperationDialog(operation, parent).exec();
}


//**********************************************************************************************************************
/// \param[in] operation The operation
/// \param[in] parent The parent widget of the dialog
//**********************************************************************************************************************
ThreadedOperationDialog::ThreadedOperationDialog(ThreadedOperation& operation, QWidget *parent)
   : QDialog(parent, Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint)
   , operation_(operation)
   , ui_(std::make_unique<Ui::ThreadedOperationDialog>())
   , thread_(nullptr)
   , canClose_(true)
{
    ui_->setupUi(this);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ThreadedOperationDialog::cleanupThread()
{
   if (!thread_)
      throw Exception(QString("%1(): trying to clean up a null thread.").arg(__FUNCTION__));
   thread_->quit();
   thread_->wait();
   thread_->deleteLater();
   thread_ = nullptr;
}


//**********************************************************************************************************************
/// \return the return code for the dialog
//**********************************************************************************************************************
int ThreadedOperationDialog::exec()
{
   ui_->labelDescription->setText(operation_.getDescription());
   ui_->labelStatus->setText(QString());
   ui_->progressBar->setRange(0, 0);
   ui_->buttonCancel->setEnabled(operation_.isCancelable());

   if (thread_)
      throw Exception(QString("%1(): The thread pointer is not null on startup.").arg(__FUNCTION__));
   thread_ = new QThread;
   operation_.moveToThread(thread_);
   connect(thread_, &QThread::started, &operation_, &ThreadedOperation::run);
   connect(&operation_, &ThreadedOperation::finished, this, &ThreadedOperationDialog::onOperationFinished);
   connect(&operation_, &ThreadedOperation::canceled, this, &ThreadedOperationDialog::onOperationCanceled);
   connect(&operation_, &ThreadedOperation::error, this, &ThreadedOperationDialog::onOperationError);
   connect(&operation_, &ThreadedOperation::statusChanged, this, &ThreadedOperationDialog::onOperationStatusChanged);
   connect(&operation_, &ThreadedOperation::progress, this, &ThreadedOperationDialog::onOperationProgress);
   canClose_ = false;
   thread_->start();
   return QDialog::exec();
}



//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ThreadedOperationDialog::onActionCancel() const
{
   if (!operation_.isCancelable())
      return;
   operation_.cancel();
   ui_->buttonCancel->setEnabled(false);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ThreadedOperationDialog::onOperationFinished()
{
   this->cleanupThread();
   canClose_ = true;
   this->accept();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void ThreadedOperationDialog::onOperationCanceled()
{
   this->cleanupThread();
   canClose_ = true;
   this->accept();
}


//**********************************************************************************************************************
/// \param[in] message The message
//**********************************************************************************************************************
void ThreadedOperationDialog::onOperationError(QString const& message)
{
   QMessageBox::critical(this, tr("Error"), message);
   this->cleanupThread();
   canClose_ = true;
   this->reject();
}


//**********************************************************************************************************************
/// \param[in] status The new status message
//**********************************************************************************************************************
void ThreadedOperationDialog::onOperationStatusChanged(QString const& status) const
{
   ui_->labelStatus->setText(status);
}


//**********************************************************************************************************************
/// \param[in] progress The current progress of the operation
//**********************************************************************************************************************
void ThreadedOperationDialog::onOperationProgress(qint32 progress) const
{
   ui_->progressBar->setRange(0, 100);
   ui_->progressBar->setValue(qBound<qint32>(0, progress, 100));
}


//**********************************************************************************************************************
/// \param[in] event The event
//**********************************************************************************************************************
void ThreadedOperationDialog::closeEvent(QCloseEvent *event)
{
   if (canClose_)
      event->accept();
   else
      event->ignore();
}


//**********************************************************************************************************************
/// \param[in] event The event
//**********************************************************************************************************************
void ThreadedOperationDialog::keyPressEvent(QKeyEvent *event)
{
   if (event->key() != Qt::Key_Escape)
      QDialog::keyPressEvent(event);
   else
      event->ignore();
}


} // namespace xmilib

