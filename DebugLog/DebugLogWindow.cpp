/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of class for debug log window
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "DebugLogWindow.h"
#include "ui_DebugLogWindow.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] debugLog The debug log
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
DebugLogWindow::DebugLogWindow(DebugLog* debugLog, QWidget *parent)
   : QWidget(parent)
   , ui_(std::make_unique<Ui::DebugLogWindow>())
   , debugLog_(debugLog)
   , lastRowWasVisible_(true)
   , filterModel_(new DebugLogFilterProxyModel(DebugLogEntry::Info | DebugLogEntry::Warning | DebugLogEntry::Error, 
      this))
{
   ui_->setupUi(this);
   this->setWindowFlags(this->windowFlags() | Qt::Window);
   if (debugLog_)
   {
      filterModel_->setSourceModel(debugLog_);
      ui_->tableView->setModel(filterModel_);
      connect(filterModel_, &DebugLog::rowsAboutToBeInserted, this, &DebugLogWindow::onRowsAboutToBeInserted);
      connect(filterModel_, &DebugLog::rowsInserted, this, &DebugLogWindow::onRowsInserted);
   }
   int const estimatedWidth(ui_->tableView->horizontalHeader()->fontMetrics()
      .boundingRect("####-##-## ##:##:##.###").width());
   ui_->tableView->setColumnWidth(0, qint32(float(estimatedWidth) * 1.05));
   ui_->tableView->horizontalHeader()->setStretchLastSection(true);
   ui_->tableView->resizeRowsToContents();
}


//**********************************************************************************************************************
/// \return true if and only if the last row of the log is visible
//**********************************************************************************************************************
bool DebugLogWindow::isLastRowVisible() const
{
   if (!filterModel_)
      return true;
   qint32 const rowCount(filterModel_->rowCount());
   return ui_->tableView->visualRect(filterModel_->index(rowCount - 1, 0)).y() 
      < ui_->tableView->viewport()->rect().height();
}


//**********************************************************************************************************************
/// \param[in] parent The parent index
/// \param[in] start The index of the first inserted row
/// \param[in] end The index of the last inserted row
//**********************************************************************************************************************
void DebugLogWindow::onRowsAboutToBeInserted(const QModelIndex &parent, int start, int end)
{
   lastRowWasVisible_ = this->isLastRowVisible();
}


//**********************************************************************************************************************
/// \param[in] parent The parent index
/// \param[in] first The index of the first inserted row
/// \param[in] last The index of the last inserted row
//**********************************************************************************************************************
void DebugLogWindow::onRowsInserted(QModelIndex const& parent, int first, int last)
{
   for (qint32 i = first; i <= last; ++i)
      ui_->tableView->resizeRowToContents(i);
   if (lastRowWasVisible_)
      ui_->tableView->scrollToBottom();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogWindow::onFilterChanged()
{
   filterModel_->setEntryTypes((ui_->checkboxInfoFilter->isChecked() ? DebugLogEntry::Info : 0)
      | (ui_->checkboxWarningFilter->isChecked() ? DebugLogEntry::Warning : 0)
      | (ui_->checkboxErrorFilter->isChecked() ? DebugLogEntry::Error : 0));
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogWindow::onActionClose()
{
   this->close();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLogWindow::onActionClearLog()
{
   if (debugLog_)
      debugLog_->clear();
}


} // namespace xmilib
