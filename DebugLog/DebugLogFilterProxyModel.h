/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of filter proxy model for DebugLog


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
	virtual ~DebugLogFilterProxyModel() override = default; ///< Default destructor
	void setEntryTypes(quint32 entryTypes); ///< Set the filter by specifying the allowed entry types

protected: // member functions
   bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const; ///< 

private: // member functions
	DebugLogFilterProxyModel(DebugLogFilterProxyModel const&); ///< Disabled copy constructor
	DebugLogFilterProxyModel& operator=(DebugLogFilterProxyModel const&); ///< Disabled assignment operator

private: // data members
   quint32 entryTypes_; ///< The allowed log entry types as a bitfield
};


} // namespace xmilib


#endif // #ifndef XMILIB__DEBUG__LOG__FILTER__PROXY__MODEL__H


