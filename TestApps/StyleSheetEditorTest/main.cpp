/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point


#include "stdafx.h"
#include "MainWindow.h"
#include <XMiLib/StyleSheetEditor.h>


using namespace xmilib;




void loadApplicationTheme(); ///< Load the theme for the application


//**********************************************************************************************************************
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The list of command-line arguments
/// \return The application exit code
//**********************************************************************************************************************
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   a.setApplicationName("Style Sheet Editor Test");
   a.setOrganizationName("x-mi.com");
   a.setOrganizationDomain("x-mi.com");
   a.setApplicationVersion("1.0");
   loadApplicationTheme();
   MainWindow w;
   w.show();
   return a.exec();
}


//**********************************************************************************************************************
/// The theme for the application is stored in a file in the application data folder
//**********************************************************************************************************************
void loadApplicationTheme()
{
   QFile file(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
      .absoluteFilePath(StyleSheetEditor::kStyleSheetFileName));
   if (!file.open(QIODevice::ReadOnly))
      return;
   qApp->setStyleSheet(file.readAll());
}