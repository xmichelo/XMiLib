/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of class for debug log window


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
{
    ui_->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::Window);
    if (debugLog_)
      ui_->tableView->setModel(debugLog);
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
   qDebug() << QString("%1()").arg(__FUNCTION__);
}


} // namespace xmilib
