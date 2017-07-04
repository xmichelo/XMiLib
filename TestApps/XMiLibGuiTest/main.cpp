/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point


#include "stdafx.h"
#include "MainWindow.h"
#include "Constants.h"
#include "OriginalStyleSheet.h"
#include <XMiLib/StyleSheetEditor/StyleSheetEditor.h>
#include <XMiLib/Exception.h>


using namespace xmilib;


void checkAndCreateDataDir(); ///< Check if the application data folder exists and create it if not


//**********************************************************************************************************************
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The list of command-line arguments
/// \return The application exit code
//**********************************************************************************************************************
int main(int argc, char *argv[])
{
   try {
      QApplication a(argc, argv);
      a.setApplicationName("XMiLib GUI Test");
      a.setOrganizationName("x-mi.com");
      a.setApplicationVersion("1.0");
      checkAndCreateDataDir();
      qApp->setStyleSheet(kOriginalStyleSheet);
      MainWindow w;
      w.show();
      return a.exec();
   }
   catch (xmilib::Exception const& e)
   {
#ifdef WIN32
      MessageBox(nullptr, LPCWSTR(e.qwhat().utf16()), L"Unhandled Exception", MB_OK | MB_ICONERROR);
#else
      qDebug() << "An unhandled exception occurred.";
#endif
   }
   catch (std::exception const& e)
   {
#ifdef WIN32
      MessageBox(nullptr, LPCWSTR(QString::fromLocal8Bit(e.what()).utf16()), L"Unhandled Exception",
         MB_OK | MB_ICONERROR);
#else
      qDebug() << "An unhandled exception occurred.";
#endif
   }
   catch (...)
   {
#ifdef WIN32
      MessageBox(nullptr, L"An unhandled exception occurred.", L"Unhandled Exception", MB_OK | MB_ICONERROR);
#else
      qDebug() << "An unhandled exception occurred.";
#endif
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void checkAndCreateDataDir()
{
   QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
   if (!dataDir.exists())
      QDir().mkpath(dataDir.absolutePath());
   if (!dataDir.exists())
      throw Exception("The application data folder could not be created.");
}