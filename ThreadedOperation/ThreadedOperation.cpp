/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of threaded operation class


#include "stdafx.h"
#include "ThreadedOperation.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] operation The threaded operation to run
/// \param[out] outErrorMessage The error message if any. This parameter is optional
//**********************************************************************************************************************
bool ThreadedOperation::runInEventLoop(ThreadedOperation& operation, QString* outErrorMessage)
{
   QEventLoop loop;
   QThread thread;
   operation.moveToThread(&thread);
   bool ok = true;
   loop.connect(&thread, &QThread::started, &operation, &ThreadedOperation::run);
   loop.connect(&operation, &ThreadedOperation::finished, &loop, &QEventLoop::quit);
   loop.connect(&operation, &ThreadedOperation::error, [&](QString const& message) { 
      ok = false;
      if (outErrorMessage)
         *outErrorMessage = message;
      loop.quit(); 
   });
   thread.start();
   loop.exec();
   thread.quit();
   while (!thread.isFinished()) {}
   return ok;
}


//**********************************************************************************************************************
/// \param[in] description The description of the operation
/// \param[in] parent The parent object of the instance
//**********************************************************************************************************************
ThreadedOperation::ThreadedOperation(QString const& description, QObject* parent)
   : QObject(parent)
   , description_(description)
{

}


//**********************************************************************************************************************
/// \return The description of the operation
//**********************************************************************************************************************
QString ThreadedOperation::getDescription() const
{
   return description_;
}


} // namespace xmilib