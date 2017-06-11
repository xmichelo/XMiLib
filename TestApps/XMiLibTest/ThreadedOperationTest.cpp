/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the ThreadedOperation class


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/ThreadedOperation/ThreadedOperation.h>


using namespace xmilib;


namespace {
   QString const kOperationDescription; ///< The description of the operation
   QString const kErrMessage; ///< The error message
}


//**********************************************************************************************************************
/// \brief Test class for successful threaded operation
//**********************************************************************************************************************
class ThreadedOperationSuccess: public ThreadedOperation {
public:
   ThreadedOperationSuccess() : ThreadedOperation(kOperationDescription) {}
   void run() override {
      emit started();
      this->thread()->msleep(100);
      emit finished();
   }
   bool isCancelable() const override { return false; }
};


//**********************************************************************************************************************
/// \brief Test class for successful threaded operation
//**********************************************************************************************************************
class ThreadedOperationFailure : public ThreadedOperation {
public:
   ThreadedOperationFailure() : ThreadedOperation(kOperationDescription) {}
   void run() override {
      emit started();
      this->thread()->msleep(100);
      emit error(kErrMessage);
   }
   bool isCancelable() const override { return false; }
};

//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::threadedOperation()
{
   try 
   {
      ThreadedOperationSuccess successOperation;
      QVERIFY2(successOperation.getDescription() == kOperationDescription, "The operation reported an invalid "
         "description");
      QVERIFY2(ThreadedOperation::runInEventLoop(successOperation), "The threaded operation failed.");
      ThreadedOperationFailure failureOperation;
      QString msg;
      QVERIFY2(!ThreadedOperation::runInEventLoop(failureOperation, &msg), "The operation supposed to fail did not.");
      QVERIFY2(kErrMessage == msg, "The operation supposed to fail reported an invalid error message.");
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception");
   }
}

