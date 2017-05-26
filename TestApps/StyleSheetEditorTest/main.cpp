/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point


#include "stdafx.h"
#include "MainWindow.h"
#include <XMiLib/StyleSheetEditor.h>


using namespace xmilib;


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
   a.setApplicationVersion("1.0");
   StyleSheetEditor::loadAndApplyStyleSheet();
   MainWindow w;
   w.show();
   return a.exec();
}
