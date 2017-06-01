/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of program entry point


#include "stdafx.h"
#include "MainWindow.h"


//**********************************************************************************************************************
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The list of command-line arguments
/// \return The exit code for the application
//**********************************************************************************************************************
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugLogTest w;
    w.show();
    return a.exec();
}
