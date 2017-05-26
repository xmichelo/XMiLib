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
   , styleSheetEditor_(nullptr)
{
   ui_.setupUi(this);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionQuit()
{
   QApplication::closeAllWindows();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void MainWindow::onActionShowStyleSheetEditor()
{
   if (!styleSheetEditor_)
      styleSheetEditor_ = new StyleSheetEditor(this);
   styleSheetEditor_->show();
}


