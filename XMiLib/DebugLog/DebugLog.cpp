/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "DebugLog.h"
#include "Exception.h"


namespace {
   QBrush const kWhiteBrush(QColor(255, 255, 255, 255)); ///< A white brush
   QBrush const kRedBrush(QColor(255, 24, 0, 255)); ///< A red brush
   QBrush const kOrangeBrush(QColor(255, 150, 0, 255)); ///< An orange brush
   QBrush const kGreenBrush(QColor(115, 200, 64, 255)); ///< A green brush
}


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] parent The parent object of the DebugLog instance
//**********************************************************************************************************************
DebugLog::DebugLog(QObject* parent)
   : QAbstractTableModel(parent)
   , entries_()
   , logFile_()
   , maxEntryCount_(0)
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
/// \note If logging to file is enabled, the content of the log file is NOT cleared
//**********************************************************************************************************************
void DebugLog::clear()
{
   this->beginResetModel();
   entries_.clear();
   this->endResetModel();
}


//**********************************************************************************************************************
/// \param[in] path The path of the file to write into
/// \return true if the log file was opened successfully for writing
//**********************************************************************************************************************
bool DebugLog::enableLoggingToFile(QString const& path)
{
   logFile_.close();
   logFile_.setFileName(path);
   return logFile_.open(QIODevice::WriteOnly);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLog::disableLoggingToFile()
{
   logFile_.close();
   logFile_.setFileName(QString());
}


//**********************************************************************************************************************
/// \return true if and only if logging to file is enabled
//**********************************************************************************************************************
bool DebugLog::isLoggingToFileEnabled() const
{
   return logFile_.isOpen();
}


//**********************************************************************************************************************
/// \return the path of the log file
//**********************************************************************************************************************
QString DebugLog::getLogFilePath() const
{
   return logFile_.fileName();
}


//**********************************************************************************************************************
/// If the maximum number of entries is reach the oldest entries are removed when new entries are added
/// \param[in] maxEntryCount The maximum number of entries in the log
//**********************************************************************************************************************
void DebugLog::setMaxEntryCount(qint32 maxEntryCount)
{
   if (maxEntryCount < 0)
      throw Exception();
   if ((0 == maxEntryCount) || (maxEntryCount >= qint32(entries_.size())))
   {
      maxEntryCount_ = maxEntryCount;
      return;
   }
   qint32 const removeCount(entries_.size() - maxEntryCount);
   Q_ASSERT(removeCount > 0);
   this->beginRemoveRows(QModelIndex(), 0, removeCount - 1);
   entries_.erase(entries_.begin(), entries_.begin() + removeCount);
   this->endRemoveRows();
   maxEntryCount_ = maxEntryCount;
}


//**********************************************************************************************************************
/// \return The maximum number of entries in the log
//**********************************************************************************************************************
qint32 DebugLog::getMaxEntryCount() const
{
   return maxEntryCount_;
}


//**********************************************************************************************************************
/// \param[in] index The index of the log entry
//**********************************************************************************************************************
SPDebugLogEntry const& DebugLog::operator[](qint64 index) const
{
   if ((index < 0) || (index >= entries_.size()))
      throw Exception(QString("Index out of range"));
   return entries_[index];
}


//**********************************************************************************************************************
/// \param[in] index The index of the log entry
//**********************************************************************************************************************
SPDebugLogEntry& DebugLog::operator[](qint64 index)
{
   return const_cast<SPDebugLogEntry&>(static_cast<const DebugLog&>(*this).operator[](index));
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
int DebugLog::rowCount(const QModelIndex&) const
{
   return int(entries_.size());
}


//**********************************************************************************************************************
//
//**********************************************************************************************************************
int DebugLog::columnCount(const QModelIndex&) const
{
   return 2;
}


//**********************************************************************************************************************
/// \param[in] index The index
/// \param[in] role The role
//**********************************************************************************************************************
QVariant DebugLog::data(const QModelIndex &index, int role) const
{
   qint32 const row = index.row();
   if ((row < 0) || (row >= qint32(entries_.size())))
      return QVariant();
   SPDebugLogEntry entry(entries_[row]);
   if (!entry.get())
      return QVariant();
   switch (role)
   {
   case Qt::ToolTipRole:
   case Qt::DisplayRole:
      switch (index.column())
      {
      case 0: return entry->getDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
      case 1: return entry->getMessage();
      default: return QVariant();
      }
   case Qt::ForegroundRole:
      return kWhiteBrush;
   case Qt::BackgroundColorRole:
   {
      int const rowIndex(index.row());
      switch (entries_[rowIndex]->getType())
      {
      case DebugLogEntry::Info:
         return kGreenBrush;
      case DebugLogEntry::Warning:
         return kOrangeBrush;
      case DebugLogEntry::Error:
         return kRedBrush;
      default:
         Q_ASSERT(false);
         return kRedBrush;
      }
   }
   default:
      return QVariant();
   }
}


//**********************************************************************************************************************
/// \param[in] section The section (column or row index depending on the orientation
/// \param[in] orientation The orientation of the header
/// \param[in] role The role
/// \return The corresponding header data
//**********************************************************************************************************************
QVariant DebugLog::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (Qt::Vertical == orientation)
      return QAbstractTableModel::headerData(section, orientation, role);
   switch (role)
   {
   case Qt::DisplayRole:
      switch (section)
      {
         case 0: return tr("Date/Time");
         case 1: return tr("Message");
         default: return QVariant();
      }
   default:
      return QAbstractTableModel::headerData(section, orientation, role);
   }
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
   // check if we can add one more line to the log, and if not, remove the oldest entry
   if ((maxEntryCount_ > 0) && (qint32(entries_.size()) >= maxEntryCount_))
   {
      this->beginRemoveRows(QModelIndex(), 0, 0);
      entries_.pop_front();
      this->endRemoveRows();
   }

   // Add the entry to the log
   this->beginInsertRows(QModelIndex(), entries_.size(), entries_.size());
   SPDebugLogEntry const logEntry(std::make_shared<DebugLogEntry>(type, message));
   entries_.push_back(logEntry);
   this->endInsertRows();

   // Write the entry to file if necessary
   if (logFile_.isOpen())
   {
      logFile_.write(logEntry->toString().toLocal8Bit() + "\n");
      logFile_.flush(); // we flush to allow live viewing and to be sure the last entries are written if the application crash
   }
}


} // namespace xmilib
