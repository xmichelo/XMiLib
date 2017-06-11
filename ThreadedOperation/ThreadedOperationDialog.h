/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of threaded operation dialog


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
	virtual ~ThreadedOperationDialog() override = default; ///< Default destructor
	void cleanupThread(); ///< Clean-up the thread

public slots:
   virtual int exec(); ///< Execute the dialog (and the operation)
   void onActionCancel(); ///< Slot for the 'Cancel' action
   void onOperationFinished(); ///< Slot for the finishing of the threaded operation
   void onOperationCanceled(); ///< Slot for the canceling of the operation
   void onOperationError(QString const& message); ///< Slot for errors in the threaded operation
   void onOperationStatusChanged(QString const& message); ///< Slot for status changes in the threaded operation
   void onOperationProgress(qint32 progress); ///< Slot of progress report of the operation

private: // member functions
	ThreadedOperationDialog(ThreadedOperationDialog const&); ///< Disabled copy constructor
	ThreadedOperationDialog& operator=(ThreadedOperationDialog const&); ///< Disabled assignment operator
   void closeEvent(QCloseEvent *event); ///< Window close event handler
   void keyPressEvent(QKeyEvent *event); ///< Key press event handler

private: // data members
   ThreadedOperation& operation_; ///< The threaded operation
   std::unique_ptr<Ui::ThreadedOperationDialog> ui_; ///< The GUI for the dialog
   QThread* thread_; ///< The thread for the operation
   bool canClose_; ///< Can the window be closed
};


} // namespace xmilib


#endif // #ifndef XMILIB__THREADED_OPERATION__DIALOG__H

