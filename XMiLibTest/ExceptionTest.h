/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of test class for xmilib::Exception


#ifndef XMILIB__TEST__EXCEPTION__TEST
#define XMILIB__TEST__EXCEPTION__TEST


//**********************************************************************************************************************
/// \brief Test class for xmilib::Exception
//**********************************************************************************************************************
class ExceptionTest : public QObject
{
   Q_OBJECT
private slots:
   void exceptionHandling(); ///< Test the exception handling
   void exceptionMessage_data(); ///< The data for exception message testing
   void exceptionMessage(); ///< Test exception message
};


#endif // #ifndef XMILIB__TEST__EXCEPTION__TEST



