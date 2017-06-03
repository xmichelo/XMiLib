/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of class for debug log window


#ifndef XMILIB__DEBUG__LOG__WINDOW__H
#define XMILIB__DEBUG__LOG__WINDOW__H


#include "DebugLog.h"
#include <memory>


namespace Ui { class DebugLogWindow; };


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for debug log window
//**********************************************************************************************************************
class DebugLogWindow: public QWidget
{
   Q_OBJECT
public: // member functions
	DebugLogWindow(DebugLog* debugLog = nullptr, QWidget* parent = nullptr); ///< Default constructor
	virtual ~DebugLogWindow() override = default; ///< Default destructor

private: // member functions
	DebugLogWindow(DebugLogWindow const&); ///< Disabled copy constructor
	DebugLogWindow& operator=(DebugLogWindow const&); ///< Disabled assignment operator
   bool isLastRowVisible() const; ///< Check whether the last row of the log is visible

private slots:
   void onRowsAboutToBeInserted(const QModelIndex &parent, int start, int end); ///< Slot for before the insertion of a row
   void onRowsInserted(QModelIndex const& parent, int first, int last); ///< Slot for the insertion of a row
   void onActionClose(); ///< Slot for the 'Close' action
   void onActionClearLog(); ///< Slot for the 'Clear Log' action

private:
   std::unique_ptr<Ui::DebugLogWindow> ui_; ///< The GUI for the window
   DebugLog* debugLog_; ///< The debug log to display
   bool lastRowWasVisible_; ///< Was the last row visible before insertion
};


} // namespace xmilib


#endif // #ifndef XMILIB__DEBUG__LOG__WINDOW__H
