/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of threaded operation class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "ThreadedOperation.h"
#include <utility>


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] operation The threaded operation to run
/// \param[out] outErrorMessage The error message if any. This parameter is optional
/// \return true if the operation completed successfully or has been canceled
//**********************************************************************************************************************
bool ThreadedOperation::runInEventLoop(ThreadedOperation& operation, QString* outErrorMessage)
{
   QEventLoop loop;
   QThread thread;
   operation.moveToThread(&thread);
   bool ok = true;
   connect(&thread, &QThread::started, &operation, &ThreadedOperation::run);
   connect(&operation, &ThreadedOperation::finished, &loop, &QEventLoop::quit);
   connect(&operation, &ThreadedOperation::canceled, &loop, &QEventLoop::quit);
   connect(&operation, &ThreadedOperation::error, [&](QString const& message) { 
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
ThreadedOperation::ThreadedOperation(QString description, QObject* parent)
   : QObject(parent)
   , description_(std::move(description))
   , canceled_(false)
{

}


//**********************************************************************************************************************
/// \return The description of the operation
//**********************************************************************************************************************
QString ThreadedOperation::getDescription() const
{
   return description_;
}


//**********************************************************************************************************************
/// \return true if and only if the operation has been canceled
//**********************************************************************************************************************
bool ThreadedOperation::isCanceled() const
{
   return canceled_.load();
}


//**********************************************************************************************************************
/// \return true if the operation cancelation has been accepted
//**********************************************************************************************************************
bool ThreadedOperation::cancel()
{
   bool const cancelable(this->isCancelable());
   if (cancelable)
      canceled_ = true;
   return cancelable;
}


} // namespace xmilib