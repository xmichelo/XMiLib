/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of filter proxy model for DebugLog
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_DEBUG_LOG_FILTER_PROXY_MODEL_H
#define XMILIB_DEBUG_LOG_FILTER_PROXY_MODEL_H


namespace xmilib {


//****************************************************************************************************************************************************
/// \brief Filter proxy model for DebugLog
//****************************************************************************************************************************************************
class DebugLogFilterProxyModel : public QSortFilterProxyModel {
Q_OBJECT
public: // member functions
    explicit DebugLogFilterProxyModel(qint32 entryTypes, QObject *parent = nullptr); ///< Default constructor
    DebugLogFilterProxyModel(DebugLogFilterProxyModel const &) = delete; ///< Disabled copy constructor
    DebugLogFilterProxyModel(DebugLogFilterProxyModel &&) = delete; ///< Disabled move copy constructor
    ~DebugLogFilterProxyModel() override = default; ///< Default destructor
    DebugLogFilterProxyModel &operator=(DebugLogFilterProxyModel const &) = delete; ///< Disabled assignment operator
    DebugLogFilterProxyModel &operator=(DebugLogFilterProxyModel &&) = delete; ///< Disabled move assignment operator
    void setEntryTypes(quint32 entryTypes); ///< Set the filter by specifying the allowed entry types

protected: // member functions
    bool filterAcceptsRow(int sourceRow, const QModelIndex &) const override; ///< Check whether a row should be displayed

private: // data members
    quint32 entryTypes_; ///< The allowed log entry types as a bitfield
};


} // namespace xmilib


#endif // #ifndef XMILIB_DEBUG_LOG_FILTER_PROXY_MODEL_H


