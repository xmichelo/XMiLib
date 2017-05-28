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
qint32 DebugLog::size() const
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
/// \param[in] parent The index of the parent model
/// \return The number of entries in log
//**********************************************************************************************************************
int DebugLog::rowCount(const QModelIndex &parent) const
{
   return int(entries_.size());
}


//**********************************************************************************************************************
/// \return The number of rows in the model
//**********************************************************************************************************************
int DebugLog::columnCount(const QModelIndex &parent) const
{
   return 2;
}


//**********************************************************************************************************************
/// \param[in] index The index
/// \param[in] role The role
//**********************************************************************************************************************
QVariant DebugLog::data(const QModelIndex &index, int role) const
{
   return QVariant();
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