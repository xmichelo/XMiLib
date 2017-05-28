/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log


#include "stdafx.h"
#include "DebugLog.h"
#include "Exception.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] parent The parent object of the DebugLog instance
//**********************************************************************************************************************
DebugLog::DebugLog(QObject* parent)
   : QAbstractTableModel(parent)
   , entries_()
{

}


//**********************************************************************************************************************
/// \return The number of entries in the log
//**********************************************************************************************************************
qint64 DebugLog::size() const
{
   return entries_.size();
}


//**********************************************************************************************************************
/// \param[in] index The index of the log entry
//**********************************************************************************************************************
SPLogEntry const& DebugLog::operator[](qint64 index) const
{
   if ((index < 0) || (index >= entries_.size()))
      throw Exception(QString("Index out of range"));
   return entries_[index];
}


//**********************************************************************************************************************
/// \param[in] index The index of the log entry
//**********************************************************************************************************************
SPLogEntry& DebugLog::operator[](qint64 index)
{
   return const_cast<SPLogEntry&>(static_cast<const DebugLog&>(*this).operator[](index));
}


//**********************************************************************************************************************
/// \param[in] message The message for the log entry
//**********************************************************************************************************************
void DebugLog::addInfo(QString const& message)
{
   this->addEntry(DebugLogEntry::Info, message);
}


//**********************************************************************************************************************
/// \param[in] message The message for the log entry
//**********************************************************************************************************************
void DebugLog::addWarning(QString const& message)
{
   this->addEntry(DebugLogEntry::Warning, message);
}


//**********************************************************************************************************************
/// \param[in] message The message for the log entry
//**********************************************************************************************************************
void DebugLog::addError(QString const& message)
{
   this->addEntry(DebugLogEntry::Error, message);
}


//**********************************************************************************************************************
/// \param[in] type The type of log entry
/// \param[in] message The log entry message
//**********************************************************************************************************************
void DebugLog::addEntry(DebugLogEntry::EType type, QString const& message)
{
   this->beginInsertRows(QModelIndex(), entries_.size(), entries_.size());
   entries_.push_back(std::make_shared<DebugLogEntry>(type, message));
   this->endInsertRows();
}


} // namespace xmilib