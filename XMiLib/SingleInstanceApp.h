/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of class that allows only a single instance of an application.
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#ifndef XMILIB_SINGLE_INSTANCE_APP_H
#define XMILIB_SINGLE_INSTANCE_APP_H


namespace xmilib {


//**********************************************************************************************************************
/// \brief A class managing a single instance of an application
//**********************************************************************************************************************
class SingleInstanceApplication: public QObject
{
   Q_OBJECT
public: // member functions
   explicit SingleInstanceApplication(QString const& appKey); ///< Default constructor.
   SingleInstanceApplication(SingleInstanceApplication const&) = delete; ///< Disabled copy-constructor.
   SingleInstanceApplication(SingleInstanceApplication&&) = delete; ///< Disabled assignment copy-constructor.
   ~SingleInstanceApplication() = default; ///< Destructor.
   SingleInstanceApplication& operator=(SingleInstanceApplication const&) = delete; ///< Disabled assignment operator.
   SingleInstanceApplication& operator=(SingleInstanceApplication&&) = delete; ///< Disabled move assignment operator.
   bool isFirstInstance() const; ///< Check whether this instance is the first instance of the application.
   bool isValid() const; ///< Is the instance of the class valid

signals:
   void anotherInstanceWasLaunched(); ///< Signal emitted when another instance is launched.

private slots:
   void onTimer(); ///< Slot for the timer.

private: // member functions
   qint32 sharedValue(); /// return the value placed in the shared memory segment
   void setSharedValue(qint32 value); /// return the value placed in the shared memory segment

private: // data membems
   QSharedMemory sharedMem_; ///< The shared memory segment.
   QTimer timer_; ///< The timer for check the shared memory segment.
   bool isFirstInstance_ { false }; ///< Is this instance the first instance of the application.
   bool isValid_ { true };
};




} // namespace xmilib


#endif // #ifndef XMILIB_SINGLE_INSTANCE_APP_H
