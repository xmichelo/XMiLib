/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_TEST_GUI_TEST_MAIN_WINDOW_H
#define XMILIB_TEST_GUI_TEST_MAIN_WINDOW_H


#include "ui_MainWindow.h"
#include <XMiLib/DebugLog/DebugLogWindow.h>
#include <XMiLib/StyleSheetEditor/StyleSheetEditor.h>


//**********************************************************************************************************************
/// \brief Main window class
//**********************************************************************************************************************
class MainWindow : public QMainWindow
{
   Q_OBJECT
public: // member functions
   explicit MainWindow(QWidget *parent = nullptr); ///< Default constructor
   MainWindow(MainWindow const&) = delete; ///< Disabled copy constructor
   MainWindow(MainWindow&&) = delete; ///< Disabled move copy constructor
   ~MainWindow() override = default; ///< Default destructor
   MainWindow& operator=(MainWindow const&) = delete; ///< Disabled assignment operator
   MainWindow& operator=(MainWindow&&) = delete; ///< Disabled move assignment operator

private: // member functions
   void addDebugLogEntry(xmilib::DebugLogEntry::EType type, QString const& message) const;

private slots:
   static void onActionQuit(); ///< Slot for the 'Quit' action
   void onActionShowStyleSheetEditor() const; ///< Slot for the theme editor window
   void onActionShowDebugLog(); ///< Slot for the 'Show Debug Log' action
   void onActionAddInfo(); ///< Slot for the 'Add Info' action
   void onActionAddWarning(); ///< Slot for the 'Add Warning' action
   void onActionAddError(); ///< Slot for the 'Add Error' action
   void onActionOpenLogFile(); ///< Slot for the 'Open Log File' action
   void onMaxEntryCountChange(int value) const; ///< Slot for the change max entry count
   void onActionLaunchThreadWithoutDialog(); ///< Slot for the 'Launch Thread Without Dialog' action
   static void onActionLaunchThreadWithDialog(); ///< Slot for the 'Launch Thread With Dialog' action

private: // data members
   Ui::MainWindow ui_; ///< The GUI for the window
   xmilib::SpDebugLog debugLog_; ///< The debug log
   xmilib::DebugLogWindow* debugLogWindow_ { nullptr }; ///< The debug log 
   xmilib::StyleSheetEditor* styleSheetEditor_ { nullptr }; ///< The theme window
};


#endif // #ifndef XMILIB_TEST_GUI_TEST_MAIN_WINDOW_H
