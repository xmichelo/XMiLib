/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_DEBUG_LOG_H
#define XMILIB_DEBUG_LOG_H


#include "DebugLogEntry.h"


namespace xmilib {


//**********************************************************************************************************************
/// \brief Debug log class
///
/// The class inherits from QAbastractTableModel, so it can be used as a model for a QTableView
//**********************************************************************************************************************
class DebugLog: public QAbstractTableModel
{
   Q_OBJECT
public: // member functions
   explicit DebugLog(QObject* parent = nullptr); ///< Default constructor
	DebugLog(DebugLog const&) = delete; ///< Disabled copy constructor
	DebugLog(DebugLog&&) = delete; ///< Disabled move copy constructor
   ~DebugLog() override = default; ///< Default destructor
	DebugLog& operator=(DebugLog const&) = delete; ///< Disabled assignment operator
   DebugLog& operator=(DebugLog&&) = delete; ///< Disabled assignment operator
   qint32 size() const; ///< Return the number of entries in the log
   void clear(); ///< Clear the log
   bool enableLoggingToFile(QString const& path); ///< Enable logging to file
   void disableLoggingToFile(); ///< Disable logging to file
   bool isLoggingToFileEnabled() const; ///< Is logging to file enabled
   QString getLogFilePath() const; ///< Retrieve the log file path
   void setMaxEntryCount(qint32 maxEntryCount); ///< Set log size limit (in number of entries). Zero means unlimited
   qint32 getMaxEntryCount() const; ///< Return the max number of entries
   SpDebugLogEntry const& operator[](qint64 index) const; ///< Return a constant reference to the log entry at the given index
   SpDebugLogEntry& operator[](qint64 index); ///< Return a mutable reference to the log entry at the given index
   int rowCount(const QModelIndex &parent) const override; ///< Return the number of rows in the model
   int columnCount(const QModelIndex &parent) const override; ///< Return the number of columns in the model
   QVariant data(const QModelIndex &index, int role) const override; ///< Return the data in the model at a given index for a given role
   QVariant headerData(int section, Qt::Orientation orientation, int role) const override; ///< Return the header data for a given section, header orientation and role

   void refreshContent(); ///< Refresh the content of the log.
public slots:
   void addInfo(QString const& message); ///< Add an informative message to the log
   void addWarning(QString const& message); ///< Add a warning message to the log
   void addError(QString const& message); ///< Add an error message to the log
   void addEntry(DebugLogEntry::EType type, QString const& message); ///< Add an entry to the log

private: // data members
   DeqSpLogEntry entries_; ///< The log entries
   QFile logFile_; ///< The log file. If null the log is not saved file
   qint32 maxEntryCount_; ///< The log size limit. zero means unlimited. The limit It does not apply to the log file.
};


typedef std::shared_ptr<DebugLog> SpDebugLog; ///< Type definition for shared pointer to debug log.


} // namespace xmilib


#endif // #ifndef XMILIB_DEBUG_LOG_H