/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of main window class


#include "ui_MainWindow.h"
#include <XMiLib/DebugLog/DebugLogWindow.h>


//**********************************************************************************************************************
/// \brief Main window class
//**********************************************************************************************************************
class DebugLogTest: public QMainWindow
{
   Q_OBJECT
public: // member functions
	DebugLogTest(QWidget* parent = nullptr); ///< Default constructor
	virtual ~DebugLogTest() override = default; ///< Default destructor
	
private: // member functions
	DebugLogTest(DebugLogTest const&); ///< Disabled copy constructor
	DebugLogTest& operator=(DebugLogTest const&); ///< Disabled assignment operator
   void addDebugLogEntry(xmilib::DebugLogEntry::EType type, QString const& message);

private slots:
   void onActionShowDebugLog(); ///< Slot for the 'Show Debug Log' action
   void onActionAddInfo(); ///< Slot for the 'Add Info' action
   void onActionAddWarning(); ///< Slot for the 'Add Warning' action
   void onActionAddError(); ///< Slot for the 'Add Error' action
   void onActionOpenLogFile(); ///< Slot for the 'Open Log File' action
   void onMaxEntryCountChange(int value); ///< Slot for the change max entry count

private:  // data members
   Ui::DebugLogTest ui_; ///< The GUI for the window
   xmilib::DebugLog debugLog_; ///< The debug log
   xmilib::DebugLogWindow* debugLogWindow_; ///< The debug log 

};
