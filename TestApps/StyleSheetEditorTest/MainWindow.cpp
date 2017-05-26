/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window


#include "stdafx.h"
#include "MainWindow.h"


using namespace xmilib;


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui_()
   , themeWindow_(nullptr)
{
   ui_.setupUi(this);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionQuit()
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   QApplication::closeAllWindows();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionShowStyleSheetEditor()
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   if (!themeWindow_.get())
      themeWindow_ = std::make_unique<StyleSheetEditor>();
   themeWindow_->show();
}


