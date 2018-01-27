/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "MainWindow.h"
#include "OriginalStyleSheet.h"
#include <XMiLib/SystemUtils.h>
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
   QString const kUnhandledException(QObject::tr("Unhandled Exception"));
   try 
   {
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
      displaySystemErrorDialog(kUnhandledException, e.qwhat());
   }
   catch (std::exception const& e)
   {
      displaySystemErrorDialog(kUnhandledException, e.what());
   }
   catch (...)
   {
      displaySystemErrorDialog(kUnhandledException, "An unhandled exception occurred.");
   }
   return 1;
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