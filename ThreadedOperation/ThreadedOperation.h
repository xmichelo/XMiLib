/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of threaded operation class


#ifndef XMILIB__THREADED__OPERATION__H
#define XMILIB__THREADED__OPERATION__H


namespace xmilib {


//**********************************************************************************************************************
/// \brief A class for threaded operation
///
/// This pure virtual class is intended to be sub-classed to implement an operation that should be threaded by
/// reimplementing the run() function.
///
/// To operate properly, the run function should emit the started() signal when starting the operation. It should also
/// emit the finish() signal on exit, or the error() signal if a problem occurs. The operation MUST NOT emit both the
/// error() and finished() signals.
///
/// Optionally, the progress of the operation can be reported using the progress() signal and statusChanged() can
/// be used to give feedback about current task performed by the operation.
//**********************************************************************************************************************
class ThreadedOperation: public QObject
{
   Q_OBJECT
public: // static member functions
   static bool runInEventLoop(ThreadedOperation& operation, QString* outErrorMessage = nullptr); ///< Run a threaded operation in event loop

public: // member functions
	ThreadedOperation(QString const& description, QObject* parent = nullptr); ///< Default constructor
	virtual ~ThreadedOperation() override = default; ///< Default destructor
   QString getDescription() const; ///< Retrieve the description of the operation

public slots:
   virtual void run() = 0; ///< Run the threaded operation

signals: 
   void progress(qint32 percentage); ///< Signal used to report the progress of the operation, as a percentage
   void started(); ///< Signal for the starting of the operation
   void finished(); ///< Signal for the ending of the operation
   void error(QString const& message); ///< Signal for errors
   void statusChanged(QString const& status); ///< Signal for reporting the operation status

private: // member functions
	ThreadedOperation(ThreadedOperation const&); ///< Disabled copy constructor
	ThreadedOperation& operator=(ThreadedOperation const&); ///< Disabled assignment operator

private: // data members
   QString description_; ///< The description of the operation
};


} // namespace xmilib


#endif // #ifndef XMILIB__THREADED__OPERATION__H
