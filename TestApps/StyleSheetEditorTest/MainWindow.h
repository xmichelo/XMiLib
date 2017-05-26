/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window



#ifndef STYLE__SHEET__EDITOR__TEST__MAIN__WINDOW__H
#define STYLE__SHEET__EDITOR__TEST__MAIN__WINDOW__H


#include "ui_MainWindow.h"
#include <XMiLib/StyleSheetEditor.h>
#include <memory>


//**********************************************************************************************************************
/// \brief Main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
   Q_OBJECT

public: // member functions
   MainWindow(QWidget *parent = nullptr); ///< Default constructor
   virtual ~MainWindow() override = default; ///< Default destructor

private: // member functions
   MainWindow(MainWindow const&); ///< Disabled copy constructor
   MainWindow& operator=(MainWindow const&); ///< Disabled assignment operator

   private slots:
   void onActionQuit(); ///< Slot for the 'Quit' action
   void onActionShowStyleSheetEditor(); ///< Slot for the theme editor window


private: // data members
   Ui::MainWindow ui_; ///< The GUI for the window
   std::unique_ptr<xmilib::StyleSheetEditor> themeWindow_; ///< The theme window
};


#endif // #ifndef STYLE__SHEET__EDITOR__TEST__MAIN__WINDOW__H
