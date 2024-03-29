/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the ThreadedOperation class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/ThreadedOperation/ThreadedOperation.h>


using namespace xmilib;


namespace {
QString const kOperationDescription; ///< The description of the operation
QString const kErrMessage; ///< The error message
}


//****************************************************************************************************************************************************
/// \brief Test class for successful threaded operation
//****************************************************************************************************************************************************
class ThreadedOperationSuccess : public ThreadedOperation {
public:
    ThreadedOperationSuccess()
        : ThreadedOperation(kOperationDescription) {}


    void run() override {
        emit started();
        QThread::msleep(100);
        emit finished();
    }


    bool isCancelable() const override { return false; }
};


//****************************************************************************************************************************************************
/// \brief Test class for successful threaded operation
//****************************************************************************************************************************************************
class ThreadedOperationFailure : public ThreadedOperation {
public:
    ThreadedOperationFailure()
        : ThreadedOperation(kOperationDescription) {}


    ThreadedOperationFailure(ThreadedOperationFailure const &) = delete;
    ThreadedOperationFailure(ThreadedOperationFailure &&) = delete;
    ThreadedOperationFailure &operator=(ThreadedOperationFailure const &) = delete;
    ThreadedOperationFailure &operator=(ThreadedOperationFailure &&) = delete;
    ~ThreadedOperationFailure() override = default; ///< Default destructor
    void run() override {
        emit started();
        QThread::msleep(100);
        emit error(kErrMessage);
    }


    bool isCancelable() const override { return false; }
};


//****************************************************************************************************************************************************
/// \brief 
//****************************************************************************************************************************************************
class ThreadedOperationCancelable : public ThreadedOperation {
public:
    // member functions
    ThreadedOperationCancelable()
        : ThreadedOperation(kOperationDescription) {}


    ThreadedOperationCancelable(ThreadedOperationCancelable const &) = delete; ///< Disabled copy constructor
    ThreadedOperationCancelable(ThreadedOperationCancelable &&) = delete; ///< Disabled move copy constructor
    ThreadedOperationCancelable &operator=(ThreadedOperationCancelable const &) = delete; ///< Disabled assignment operator
    ThreadedOperationCancelable &operator=(ThreadedOperationCancelable &&) = delete; ///< Disabled move assignment operator
    ~ThreadedOperationCancelable() override = default; ///< Default destructor
    void run() override {
        emit started();
        for (qint32 i = 0; i < 100; ++i) {
            if (this->isCanceled()) {
                emit canceled();
                return;
            }
            QThread::msleep(100);
            emit finished();
        }
    }


    bool isCancelable() const override { return true; }
};


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::threadedOperationSuccess() {
    try {
        ThreadedOperationSuccess successOperation;
        QVERIFY2(successOperation.getDescription() == kOperationDescription, "The operation reported an invalid "
                                                                             "description");
        QVERIFY2(ThreadedOperation::runInEventLoop(successOperation), "The threaded operation failed.");
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception");
    }
}


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::threadedOperationFailure() {
    try {
        ThreadedOperationFailure failureOperation;
        QString msg;
        QVERIFY2(!ThreadedOperation::runInEventLoop(failureOperation, &msg), "The operation supposed to fail did not.");
        QVERIFY2(kErrMessage == msg, "The operation supposed to fail reported an invalid error message.");
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception");
    }
}


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void XMiLibTest::threadedOperationCancel() {
    try {
        QEventLoop loop;
        ThreadedOperationCancelable operation;
        QVERIFY2(operation.isCancelable(), "The cancelable operation reports itself as non cancelable.");
        QThread thread;
        operation.moveToThread(&thread);
        enum {
            Running, Finished, Canceled, Error
        } status = Running;
        connect(&thread, &QThread::started, &operation, &ThreadedOperationCancelable::run);
        connect(&operation, &ThreadedOperationCancelable::canceled, [&]() {
            status = Canceled;
            loop.quit();
        });
        connect(&operation, &ThreadedOperationCancelable::finished, [&]() {
            status = Finished;
            loop.quit();
        });
        connect(&operation, &ThreadedOperationCancelable::error, [&](QString const &) {
            status = Error;
            loop.quit();
        });
        QElapsedTimer timer;
        timer.start();
        thread.start();
        while (true) {
            loop.processEvents();
            if (Running != status)
                break;
            if (!operation.isCanceled() && (timer.elapsed() > 10))
                operation.cancel();
        }
        thread.quit();
        thread.wait();

        QVERIFY2(status != Error, "The operation supposed to be canceled returned an error.");
        QVERIFY2(status != Finished, "The operation supposed to be canceled finished completely.");
        QVERIFY2(status == Canceled, "The operation supposed to be canceled was not canceled.");
    }
    catch (...) {
        QVERIFY2(false, "The function threw an exception");
    }
}


