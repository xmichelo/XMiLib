/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for the string utility functions in XMiLib


#ifndef XMILIB__TEST__STRING__UTILS__TEST
#define XMILIB__TEST__STRING__UTILS__TEST


//**********************************************************************************************************************
/// \brief 
//**********************************************************************************************************************
class StringUtilsTest: public QObject
{
   Q_OBJECT
public: // member functions
	StringUtilsTest(); ///< Default constructor
	~StringUtilsTest(); ///< Default destructor
private slots: 
   void byteToHexString_data(); /// Test data for the byteToHexString() function
   void byteToHexString(); /// Test routine for the byteToHexString() function  

private: // member functions
	StringUtilsTest(StringUtilsTest const&); ///< Disabled copy constructor
	StringUtilsTest& operator=(StringUtilsTest const&); ///< Disabled assignment operator
};


#endif // #ifndef XMILIB__TEST__STRING__UTILS__TEST