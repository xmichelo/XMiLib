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


//****************************************************************************************************************************************************
/// \param[in] argc The number of command-line arguments
/// \param[in] argv The list of command-line arguments
/// \return The application exit code
//****************************************************************************************************************************************************
int main(int argc, char *argv[]) {
    QString const unhandledException(QObject::tr("Unhandled Exception"));
    try {
        QApplication a(argc, argv);
        QApplication::setApplicationName("XMiLib GUI Test");
        QApplication::setOrganizationName("x-mi.com");
        QApplication::setApplicationVersion("1.0");
        checkAndCreateDataDir();
        dynamic_cast<QApplication *>(QCoreApplication::instance())->setStyleSheet(kOriginalStyleSheet);
        MainWindow w;
        w.show();
        return QApplication::exec();
    }
    catch (Exception const &e) {
        displaySystemErrorDialog(unhandledException, e.qwhat());
    }
    catch (std::exception const &e) {
        displaySystemErrorDialog(unhandledException, e.what());
    }
    catch (...) {
        displaySystemErrorDialog(unhandledException, "An unhandled exception occurred.");
    }
    return 1;
}


//****************************************************************************************************************************************************
// 
//****************************************************************************************************************************************************
void checkAndCreateDataDir() {
    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
    if ((!dataDir.exists()) && (!QDir().mkpath(dataDir.absolutePath())))
        throw Exception("The application data folder could not be created.");
}