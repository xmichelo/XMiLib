/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for the XMiLib library
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_TEST_H
#define XMILIB_TEST_H


#include <stdafx.h>


//**********************************************************************************************************************
/// \brief Test class for the XMiLib library
//**********************************************************************************************************************
class XMiLibTest: public QObject
{
   Q_OBJECT
public: // member functions
	XMiLibTest() = default; ///< Default constructor
   XMiLibTest(XMiLibTest const&) = delete; ///< Disabled copy constructor
   XMiLibTest(XMiLibTest&&) = delete; ///< Disabled move constructor
	~XMiLibTest() override = default; ///< Default destructor
   XMiLibTest& operator=(XMiLibTest const&) = delete; ///< Disabled assignment operator
   XMiLibTest& operator=(XMiLibTest&&) = delete; ///< Disabled move assignment operator
	
private slots:
   // ReSharper disable CppInconsistentNaming
   static void exceptionHandling(); ///< Test function for xmilib::Exception exception handling
   static void exceptionMessage_data(); ///< Test data for xmilib::Exception messages
   static void exceptionMessage(); ///< Test function for xmilib::Exception messages 
   static void fileUtilsGetRandomFileName(); ///< Test function for xmilib::getRandomFileName()
   static void fileUtilsGetTempFilePath(); ///< Test function for xmilib::getTempFilePath()
   static void fileUtilsCreateTempDir(); ///< Test function for xmilib::createTempDir()
   static void fileUtilsCreateTempFile(); ///< Test function for xmilib::createTempFile()
   static void stringUtilsByteToHexString_data(); ///< Test data for xmilib::byteToHexString()
   static void stringUtilsByteToHexString(); ///< Test function for xmilib::byteToHexString()
   static void stringUtilsByteArrayToHexString_data(); ///< Test data for xmilib::byteToHexString()
   static void stringUtilsByteArrayToHexString(); ///< Test function for xmilib::byteToHexString()
   static void stringUtilsBoolToString(); ///< Test function for xmilib::boolToString()
   static void stringUtilsToAndFromJsonDoc(); ///< Test function for xmilib::stringListToJsonDocument() xmilib::jsonDocumentToStringList()
   static void stringUtilsToAndFromJsonFile(); ///< Test function for xmilib::saveStringListToJsonFile() xmilib::loadStringListFromJsonFile()
   static void randomNumberGeneratorRange_data(); ///< Test data for the first randomness test
   static void randomNumberGeneratorRange(); ///< Test the range of the value returned by the random number generator
   static void randomNumberGeneratorRandomness(); ///< Test the randomness of the values returned by the random number generator
   static void randomNumberGeneratorSeed(); ///< Test the seed mechanics of the random number generator
   static void debugLogSize(); ///< Test the size of the debug log
   static void debugLogContents(); ///< Test the contents of the debug log
   static void debugLogTableModel(); ///< Test the table model for the debug log
   static void debugLogFile(); ///< Test logging to file
   static void threadedOperationSuccess(); ///< Test successful cases for the ThreadedOperation class
   static void threadedOperationFailure(); ///< Test failure cases for the ThreadedOperation class
   static void threadedOperationCancel(); ///< Test for canceling of threaded operation
   static void csvIo(); ///< Test the CSV I/O routines.
#ifdef Q_OS_WINDOWS
   static void globalShortcut(); ///< Test for the global shortcut classes
   static void scopedGlobalMemoryLock(); ///< Test the ScopedGlobalMemoryLock class.
   static void scopedClipboardAccess(); ///< Test the ScopedClipboardAccess class.
#endif
   // ReSharper restore CppInconsistentNaming
};


#endif // #ifndef XMILIB_TEST_H
