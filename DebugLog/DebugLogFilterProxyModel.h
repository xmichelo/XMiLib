/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of filter proxy model for DebugLog
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__DEBUG__LOG__FILTER__PROXY__MODEL__H
#define XMILIB__DEBUG__LOG__FILTER__PROXY__MODEL__H


namespace xmilib {


//**********************************************************************************************************************
/// \brief Filter proxy model for DebugLog
//**********************************************************************************************************************
class DebugLogFilterProxyModel : public QSortFilterProxyModel
{
   Q_OBJECT
public: // member functions
	DebugLogFilterProxyModel(qint32 entryTypes, QObject* parent = nullptr); ///< Default constructor
	DebugLogFilterProxyModel(DebugLogFilterProxyModel const&) = delete; ///< Disabled copy constructor
	DebugLogFilterProxyModel(DebugLogFilterProxyModel&&) = delete; ///< Disabled move copy constructor
	virtual ~DebugLogFilterProxyModel() override = default; ///< Default destructor
	DebugLogFilterProxyModel& operator=(DebugLogFilterProxyModel const&) = delete; ///< Disabled assignment operator
	DebugLogFilterProxyModel& operator=(DebugLogFilterProxyModel&&) = delete; ///< Disabled move assignment operator
	void setEntryTypes(quint32 entryTypes); ///< Set the filter by specifying the allowed entry types

protected: // member functions
   virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override; ///< Check whether a row should be displayed

private: // data members
   quint32 entryTypes_; ///< The allowed log entry types as a bitfield
};


} // namespace xmilib


#endif // #ifndef XMILIB__DEBUG__LOG__FILTER__PROXY__MODEL__H


