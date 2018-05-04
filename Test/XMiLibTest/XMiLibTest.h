/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for the XMiLib library
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__TEST__H
#define XMILIB__TEST__H


//**********************************************************************************************************************
/// \brief Test class for the XMiLib library
//**********************************************************************************************************************
class XMiLibTest: public QObject
{
   Q_OBJECT
public: // member functions
	XMiLibTest(); ///< Default constructor
	~XMiLibTest() = default; ///< Default destructor
	
private: // member functions
   XMiLibTest(XMiLibTest const&) = delete; ///< Disabled copy constructor
   XMiLibTest(XMiLibTest&&) = delete; ///< Disabled move constructor
   XMiLibTest& operator=(XMiLibTest const&) = delete; ///< Disabled assignment operator
   XMiLibTest& operator=(XMiLibTest&&) = delete; ///< Disabled move assignment operator

private slots:
   static void exceptionHandling(); ///< Test function for xmilib::Exception exception handling
   static void exceptionMessage_data(); ///< Test data for xmilib::Exception messages 
   static void exceptionMessage(); ///< Test function for xmilib::Exception messages 
   static void fileUtils_getRandomFileName(); ///< Test function for xmilib::getRandomFileName()
   static void fileUtils_createTempDir(); ///< Test function for xmilib::createTempDir()
   static void fileUtils_createTempFile(); ///< Test function for xmilib::createTempFile()
   static void stringUtils_byteToHexString_data(); ///< Test data for xmilib::byteToHexString()
   static void stringUtils_byteToHexString(); ///< Test function for xmilib::byteToHexString()
   static void stringUtils_byteArrayToHexString_data(); ///< Test data for xmilib::byteToHexString()
   static void stringUtils_byteArrayToHexString(); ///< Test function for xmilib::byteToHexString()
   static void randomNumberGenerator_range_data(); ///< Test data for the first randomness test
   static void randomNumberGenerator_range(); ///< Test the range of the value returned by the random number generator
   static void randomNumberGenerator_randomness(); ///< Test the randomness of the values returned by the random number generator
   static void randomNumberGenerator_seed(); ///< Test the seed mechanics of the random number generator
   static void debugLog_size(); ///< Test the size of the debug log
   static void debugLog_contents(); ///< Test the contents of the debug log
   static void debugLog_tableModel(); ///< Test the table model for the debug log
   static void debugLog_file(); ///< Test logging to file
   static void threadedOperation_success(); ///< Test successful cases for the ThreadedOperation class
   static void threadedOperation_failure(); ///< Test failure cases for the ThreadedOperation class
   static void threadedOperation_cancel(); ///< Test for canceling of threaded operation
   static void globalShortcut(); ///< Test for the global shortcut classes
};


#endif // #ifndef XMILIB__TEST__H
