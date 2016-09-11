/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window class


#ifndef XMILIBTEST__MAINWINDOW__H
#define XMILIBTEST__MAINWINDOW__H


#include "ui_MainWindow.h"


//**********************************************************************************************************************
/// \brief Main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
   Q_OBJECT
    
public: // member functions
   MainWindow(QWidget *parent = nullptr); ///< Default constructor
   ~MainWindow(); ///< Destructor

private: // member functions
   MainWindow(MainWindow const&); ///< Disabled copy-constructor
   MainWindow& operator=(MainWindow const&); ///< Disabled assignment operator

private: // data members
   Ui::MainWindowClass ui_; ///< The GUI for the window
};


#endif // #ifndef XMILIBTEST__MAINWINDOW__H
