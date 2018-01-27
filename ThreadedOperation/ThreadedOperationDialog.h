/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of threaded operation dialog
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__THREADED_OPERATION__DIALOG__H
#define XMILIB__THREADED_OPERATION__DIALOG__H


#include "ThreadedOperation.h"
#include <memory>


namespace Ui { class ThreadedOperationDialog; };


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for the threaded operation dialog
//**********************************************************************************************************************
class ThreadedOperationDialog: public QDialog
{
   Q_OBJECT
public: // static member functions
   static bool run(ThreadedOperation& operation, QWidget* parent = nullptr); ///< Run an operation in a threaded operation dialog

public: // member functions
	ThreadedOperationDialog(ThreadedOperation& operation, QWidget* parent = nullptr); ///< Default constructor
	ThreadedOperationDialog(ThreadedOperationDialog const&) = delete; ///< Disabled copy constructor
	ThreadedOperationDialog(ThreadedOperationDialog&&) = delete; ///< Disabled move copy constructor
	virtual ~ThreadedOperationDialog() override = default; ///< Default destructor
	ThreadedOperationDialog& operator=(ThreadedOperationDialog const&) = delete; ///< Disabled assignment operator
	ThreadedOperationDialog& operator=(ThreadedOperationDialog&&) = delete; ///< Disabled move assignment operator
	void cleanupThread(); ///< Clean-up the thread

public slots:
   int exec() override; ///< Execute the dialog (and the operation)
   void onActionCancel() const; ///< Slot for the 'Cancel' action
   void onOperationFinished(); ///< Slot for the finishing of the threaded operation
   void onOperationCanceled(); ///< Slot for the canceling of the operation
   void onOperationError(QString const& message); ///< Slot for errors in the threaded operation
   void onOperationStatusChanged(QString const& message) const; ///< Slot for status changes in the threaded operation
   void onOperationProgress(qint32 progress) const; ///< Slot of progress report of the operation

private: // member functions
   virtual void closeEvent(QCloseEvent *event) override; ///< Window close event handler
   virtual void keyPressEvent(QKeyEvent *event) override; ///< Key press event handler

private: // data members
   ThreadedOperation& operation_; ///< The threaded operation
   std::unique_ptr<Ui::ThreadedOperationDialog> ui_; ///< The GUI for the dialog
   QThread* thread_; ///< The thread for the operation
   bool canClose_; ///< Can the window be closed
};


} // namespace xmilib


#endif // #ifndef XMILIB__THREADED_OPERATION__DIALOG__H

