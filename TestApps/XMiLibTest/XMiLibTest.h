/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for the XMiLib library


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
	XMiLibTest(XMiLibTest const&); ///< Disabled copy constructor
	XMiLibTest& operator=(XMiLibTest const&); ///< Disabled assignment operator

private slots:
   void exceptionHandling(); ///< Test function for xmilib::Exception exception handling
   void exceptionMessage_data(); ///< Test data for xmilib::Exception messages 
   void exceptionMessage(); ///< Test function for xmilib::Exception messages 
   void stringUtils_byteToHexString_data(); ///< Test data for xmilib::byteToHexString()
   void stringUtils_byteToHexString(); ///< Test function for xmilib::byteToHexString()
   void stringUtils_byteArrayToHexString_data(); ///< Test data for xmilib::byteToHexString()
   void stringUtils_byteArrayToHexString(); ///< Test function for xmilib::byteToHexString()
   void randomNumberGenerator_range_data(); ///< Test data for the first randomness test
   void randomNumberGenerator_range(); ///< Test the range of the value returned by the random number generator
   void randomNumberGenerator_randomness(); ///< Test the randomness of the values returned by the random number generator
   void randomNumberGenerator_seed(); ///< Test the seed mechanics of the random number generator
   void debugLog_size(); ///< Test the size of the debug log
   void debugLog_contents(); ///< Test the contents of the debug log
   void debugLog_tableModel(); ///< Test the table model for the debug log
   void threadedOperation_success(); ///< Test successful cases for the ThreadedOperation class
   void threadedOperation_failure(); ///< Test failure cases for the ThreadedOperation class
   void threadedOperation_cancel(); ///< Test for canceling of threaded operation
};


#endif // #ifndef XMILIB__TEST__H
