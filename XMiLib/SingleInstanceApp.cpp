/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of Qt application class that allows only a single instance
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "SingleInstanceApp.h"
#include <Exception.h>


namespace {
qint32 kBufferSize = sizeof(qint32); ///< The size of the shared buffer.
qint32 kTimerIntervalMs = 200; ///< The timer interval in milliseconds.
}


namespace xmilib {


//****************************************************************************************************************************************************
/// \param[in] appKey The key identifying the application.
//****************************************************************************************************************************************************
SingleInstanceApplication::SingleInstanceApplication(QString const &appKey)
    : sharedMem_(appKey) {
    try {
        isFirstInstance_ = sharedMem_.create(kBufferSize);
        if (isFirstInstance_) {
            this->setSharedValue(0);
            connect(&timer_, &QTimer::timeout, this, &SingleInstanceApplication::onTimer);
            timer_.start(kTimerIntervalMs); ///< we check every half second if another instance has
        } else {
            if (!sharedMem_.attach())
                throw Exception();
            this->setSharedValue(1);
        }
    }
    catch (Exception const &) {
        isValid_ = false;
    }
}


//****************************************************************************************************************************************************
/// \return true if no other instance of the application was running when this instance was created.
//****************************************************************************************************************************************************
bool SingleInstanceApplication::isFirstInstance() const {
    return isFirstInstance_;
}


//****************************************************************************************************************************************************
/// \return true if and only if the instance of the class was properly setup
//****************************************************************************************************************************************************
bool SingleInstanceApplication::isValid() const {
    return isValid_;
}


//****************************************************************************************************************************************************
//
//****************************************************************************************************************************************************
void SingleInstanceApplication::onTimer() {
    try {
        qint32 const value = this->sharedValue();
        if (1 != value)
            return;
        this->setSharedValue(0);
        emit anotherInstanceWasLaunched(); ///< Signal emitted when another instance is launched.
    }
    catch (Exception const &) {
    }
}


//****************************************************************************************************************************************************
/// \return the value in the shared buffer
//****************************************************************************************************************************************************
qint32 SingleInstanceApplication::sharedValue() {
    if (!sharedMem_.lock())
        throw Exception();
    qint32 const result = *static_cast<qint32 *>(sharedMem_.data());
    sharedMem_.unlock();
    return result;
}


//****************************************************************************************************************************************************
/// \param[in] value The value to put in the shared buffer
//****************************************************************************************************************************************************
void SingleInstanceApplication::setSharedValue(qint32 value) {
    if (!sharedMem_.lock())
        throw Exception();
    *static_cast<qint32 *>(sharedMem_.data()) = value;
    sharedMem_.unlock();
}


}

