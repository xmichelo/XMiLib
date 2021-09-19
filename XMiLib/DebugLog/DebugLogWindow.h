/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of class for debug log window
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_DEBUG_LOG_WINDOW_H
#define XMILIB_DEBUG_LOG_WINDOW_H


#include "DebugLog.h"
#include "DebugLogFilterProxyModel.h"
#include <memory>


// ReSharper disable once CppInconsistentNaming
namespace Ui { class DebugLogWindow; }


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for debug log window
//**********************************************************************************************************************
class DebugLogWindow: public QWidget
{
   Q_OBJECT
public: // member functions
   explicit DebugLogWindow(SpDebugLog debugLog = nullptr, QWidget* parent = nullptr); ///< Default constructor
	DebugLogWindow(DebugLogWindow const&) = delete; ///< Disabled copy constructor
	DebugLogWindow(DebugLogWindow&&) = delete; ///< Disabled move copy constructor
   ~DebugLogWindow() override; ///< Default destructor
	DebugLogWindow& operator=(DebugLogWindow const&) = delete; ///< Disabled assignment operator
	DebugLogWindow& operator=(DebugLogWindow&&) = delete; ///< Disabled move assignment operator

private: // member functions
   bool isLastRowVisible() const; ///< Check whether the last row of the log is visible

private slots:
   void onRowsAboutToBeInserted(const QModelIndex&, int, int); ///< Slot for before the insertion of a row
   void onRowsInserted(QModelIndex const&, int first, int last) const; ///< Slot for the insertion of a row
   void onFilterChanged() const; ///< Slot for the changing of the filtering
   void onActionClose(); ///< Slot for the 'Close' action
   void onActionClearLog() const; ///< Slot for the 'Clear Log' action

private:
   std::unique_ptr<Ui::DebugLogWindow> ui_; ///< The GUI for the window
   SpDebugLog debugLog_; ///< The debug log to display
   bool lastRowWasVisible_; ///< Was the last row visible before insertion
   DebugLogFilterProxyModel* filterModel_; ///< The filter proxy model
};


} // namespace xmilib


#endif // #ifndef XMILIB_DEBUG_LOG_WINDOW_H
