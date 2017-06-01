/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log


#ifndef XMILIB__DEBUG__LOG__H
#define XMILIB__DEBUG__LOG__H


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
	DebugLog(QObject* parent = nullptr); ///< Default constructor
	virtual ~DebugLog() override = default; ///< Default destructor
   qint32 size() const; ///< Return the number of entries in the log
   void clear(); ///< Clear the log
   SPDebugLogEntry const& operator[](qint64 index) const; ///< Return a constant reference to the log entry at the given index
   SPDebugLogEntry& operator[](qint64 index); ///< Return a mutable reference to the log entry at the given index
   virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override; ///< Return the number of rows in the model
   virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override; ///< Return the number of columns in the model
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; ///< Return the data in the model at a given index for a given role
   QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const; ///< Return the header data for a given section, header orientation and role

public slots:
   void addInfo(QString const& message); ///< Add an informative message to the log
   void addWarning(QString const& message); ///< Add a warning message to the log
   void addError(QString const& message); ///< Add an error message to the log
   void addEntry(DebugLogEntry::EType type, QString const& message); ///< Add an entry to the log

private: // member functions
	DebugLog(DebugLog const&); ///< Disabled copy constructor
	DebugLog& operator=(DebugLog const&); ///< Disabled assignment operator

private: // data members
   DeqSPLogEntry entries_; ///< The log entries

   /// \todo implement limitation of number of entries in a log
   /// \todo implement logging to file
};


} // namespace xmilib


#endif // #ifndef XMILIB__DEBUG__LOG__H