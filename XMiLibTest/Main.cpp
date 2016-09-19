/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of program entry point


#include "stdafx.h"
#include "moc_ExceptionTest.cpp"
#include "moc_StringUtilsTest.cpp"

//**********************************************************************************************************************
/// \brief Program entry-point
///
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The list of command-line arguments
/// \return the return code for the application
//**********************************************************************************************************************
qint32 main(int argc, char** argv)
{
   QCoreApplication app(argc, argv); 
   app.setAttribute(Qt::AA_Use96Dpi, true); 

   QTEST_SET_MAIN_SOURCE_PATH 
   QTest::qExec(&ExceptionTest(), argc, argv);
   QTest::qExec(&StringUtilsTest(), argc, argv);
   //QCoreApplication app(argc, argv);
   //app.setAttribute(Qt::AA_Use96Dpi, true);
   ////QTEST_DISABLE_KEYPAD_NAVIGATION 
   ////QTEST_ADD_GPU_BLACKLIST_SUPPORT
   //QTEST_SET_MAIN_SOURCE_PATH 
   //bool ok(true);
   //ExceptionTest et;
   //ok = ok || (0 == QTest::qExec(&et, argc, argv));
   //ok = ok || (0 == QTest::qExec(&(StringUtilsTest()), argc, argv));
   //return ok ? 0 : 1;
}
