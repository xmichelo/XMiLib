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
	~XMiLibTest(); ///< Default destructor
	
private: // member functions
	XMiLibTest(XMiLibTest const&); ///< Disabled copy constructor
	XMiLibTest& operator=(XMiLibTest const&); ///< Disabled assignment operator

private slots:
   void exceptionHandling(); ///< Test function for xmilib::Exception exception handling
   void exceptionMessage_data(); ///< Test data for xmilib::Exception messages 
   void exceptionMessage(); ///< Test function for xmilib::Exception messages 
   void stringUtils_byteToHexString_data(); ///< Test data for xmilib::byteToHexString()
   void stringUtils_byteToHexString(); ///< Test function for xmilib::byteToHexString()
};


#endif // #ifndef XMILIB__TEST__H
