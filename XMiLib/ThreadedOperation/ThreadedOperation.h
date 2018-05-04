/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of threaded operation class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__THREADED__OPERATION__H
#define XMILIB__THREADED__OPERATION__H


namespace xmilib {


//**********************************************************************************************************************
/// \brief A class for threaded operation
///
/// This pure virtual class is intended to be sub-classed to implement an operation that should be threaded by
/// reimplementing the run() function.
///
/// The user must decide whether the operation is cancelable by providing an implementation of the base function
/// isCancelable() that returns true if the operation is cancelable.
///
/// If the use decides the operation is cancelable, he commits to periodically check for cancellation using the
/// isCanceled() function, and to reply accordingly by performing some clean-up, emiting the canceled() signal
/// and returning as soon as possible (without emiting finished() or error() signal().
///
/// To operate properly, the run function should emit the started() signal when starting the operation. It should also
/// emit the finish() signal on exit, or the error() signal if a problem occurs. The operation must emit only one
/// of the error() finished() and canceled() before exiting. 
///
/// Optionally, the progress of the operation can be reported using the progress() signal and statusChanged() can
/// be used to give feedback about current task performed by the operation.
///
//**********************************************************************************************************************
class ThreadedOperation: public QObject
{
   Q_OBJECT
public: // static member functions
   static bool runInEventLoop(ThreadedOperation& operation, QString* outErrorMessage = nullptr); ///< Run a threaded operation in event loop

public: // member functions
	ThreadedOperation(QString const& description, QObject* parent = nullptr); ///< Default constructor
	ThreadedOperation(ThreadedOperation const&) = delete; ///< Disabled copy constructor
	ThreadedOperation(ThreadedOperation&&) = delete; ///< Disabled move copy constructor
	virtual ~ThreadedOperation() override = default; ///< Default destructor
	ThreadedOperation& operator=(ThreadedOperation const&) = delete; ///< Disabled assignment operator
	ThreadedOperation& operator=(ThreadedOperation&&) = delete; ///< Disabled move assignment operator
   QString getDescription() const; ///< Retrieve the description of the operation
   bool isCanceled() const; ///< Check whether the operation has been canceled
   virtual bool isCancelable() const = 0; ///< Can the operation be canceled

public slots:
   virtual void run() = 0; ///< Run the threaded operation
   virtual bool cancel(); ///< Cancel the threaded operation

signals: 
   void progress(qint32 percentage); ///< Signal used to report the progress of the operation, as a percentage
   void started(); ///< Signal for the starting of the operation
   void finished(); ///< Signal for the ending of the operation
   void error(QString const& message); ///< Signal for errors
   void canceled(); ///< Signal for when the operation has been canceled
   void statusChanged(QString const& status); ///< Signal for reporting the operation status

private: // data members
   QString description_; ///< The description of the operation
   QAtomicInt canceled_; ///< Was the operation canceled
};


} // namespace xmilib


#endif // #ifndef XMILIB__THREADED__OPERATION__H
