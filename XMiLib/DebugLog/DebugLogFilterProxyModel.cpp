/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of filter proxy model for DebugLog
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "DebugLogFilterProxyModel.h"
#include "DebugLog.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] entryTypes The allowed log entry types
/// \param[in] parent The parent object of the instance
//**********************************************************************************************************************
DebugLogFilterProxyModel::DebugLogFilterProxyModel(qint32 entryTypes, QObject *parent)
   : QSortFilterProxyModel(parent)
   , entryTypes_(entryTypes)
{
}


//**********************************************************************************************************************
/// \param[in] entryTypes The allowed log entry types
//**********************************************************************************************************************
void DebugLogFilterProxyModel::setEntryTypes(quint32 entryTypes)
{
   entryTypes_ = entryTypes;
   this->invalidateFilter();
}


//**********************************************************************************************************************
/// \param[in] sourceRow The row in the source model
/// \return true if and only if the specified row should be included in the model
//**********************************************************************************************************************
bool DebugLogFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex&) const
{
   DebugLog* model = dynamic_cast<DebugLog*>(this->sourceModel());
   if (!model)
      return false;
   if ((sourceRow < 0) || (sourceRow >= model->rowCount()))
      return false;
   SPDebugLogEntry entry((*model)[sourceRow]);
   if (!entry.get())
      return false;
   return entry->getType() & entryTypes_;
}


} // namespace xmilib
