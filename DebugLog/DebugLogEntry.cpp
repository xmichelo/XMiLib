/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of debug log entry class


#include "stdafx.h"
#include "DebugLogEntry.h"


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] type The log entry type
/// \param[in] message The message
//**********************************************************************************************************************
DebugLogEntry::DebugLogEntry(EType type, QString const& message)
   : dateTime_(QDateTime::currentDateTime())
   , type_(type)
   , message_(message)
{

}


//**********************************************************************************************************************
/// \return The date/time of the log entry
//**********************************************************************************************************************
QDateTime DebugLogEntry::getDateTime() const
{
   return dateTime_;
}


//**********************************************************************************************************************
/// \return The log entry type
//**********************************************************************************************************************
xmilib::DebugLogEntry::EType DebugLogEntry::getType() const
{
   return type_;
}


//**********************************************************************************************************************
/// \return The log message
//**********************************************************************************************************************
QString DebugLogEntry::getMessage() const
{
   return message_;
}


//**********************************************************************************************************************
/// \return The log entry as a string
//**********************************************************************************************************************
QString DebugLogEntry::toString() const
{
   return QString("%1 - %2 - %3").arg(dateTime_.toString("yyyy-MM-dd HH:mm:ss.zzz"))
      .arg(DebugLogEntry::Info == type_ ? "INFO   " : (DebugLogEntry::Warning == type_ ? "WARNING" : "ERROR  "))
      .arg(message_);
}


} // namespace xmilib
