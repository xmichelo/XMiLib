/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log


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
/// \param[in] logFilePath The path of the log file. If null the log is not saved to file
/// \param[in] parent The parent object of the DebugLog instance
//**********************************************************************************************************************
DebugLog::DebugLog(QString const& logFilePath, QObject* parent)
   : QAbstractTableModel(parent)
   , entries_()
   , logFile_(logFilePath)
{
   if (!logFilePath.isEmpty())
      if (!logFile_.open(QIODevice::WriteOnly | QIODevice::Text))
         throw Exception("Could not open the log file.");
}


//**********************************************************************************************************************
/// \return The number of entries in the log
//**********************************************************************************************************************
qint32 DebugLog::size() const
{
   return entries_.size();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void DebugLog::clear()
{
   this->beginResetModel();
   entries_.clear();
   this->endResetModel();
}


//**********************************************************************************************************************
/// \return the path of the log file
//**********************************************************************************************************************
QString DebugLog::getLogFilePath() const
{
   return logFile_.fileName();
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
   qint32 const row = index.row();
   if ((row < 0) || (row >= entries_.size()))
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
   this->beginInsertRows(QModelIndex(), entries_.size(), entries_.size());
   SPDebugLogEntry const logEntry(std::make_shared<DebugLogEntry>(type, message));
   entries_.push_back(logEntry);
   if (logFile_.isOpen())
   {
      logFile_.write(logEntry->toString().toLocal8Bit() + "\n");
      logFile_.flush(); // we flush to allow live viewing and to be sure the last entries are written if the application crash
   }
   this->endInsertRows();
}


} // namespace xmilib