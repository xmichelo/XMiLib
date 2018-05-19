/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of debug log entry class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_DEBUG_LOG_ENTRY_H
#define XMILIB_DEBUG_LOG_ENTRY_H


#include <memory>
#include <deque>


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for debug log entry
//**********************************************************************************************************************
class DebugLogEntry
{
public: // data structures
   /// \brief Enumeration for log entry type
   enum EType {
      Info     = 1 << 0,   ///< Informative message
      Warning  = 1 << 1,   ///< Warning message
      Error    = 1 << 2,   ///< Error message
   };

public: // member functions
	DebugLogEntry(EType type, QString message); ///< Default constructor
	DebugLogEntry(DebugLogEntry const&) = delete; ///< Disabled copy constructor
   DebugLogEntry(DebugLogEntry&&) = delete; ///< Disabled move constructor
	~DebugLogEntry() = default; ///< Default destructor
	DebugLogEntry& operator=(DebugLogEntry const&) = delete; ///< Disabled assignment operator
   DebugLogEntry& operator=(DebugLogEntry&&) = delete; ///< Disabled move assignment operator
	QDateTime getDateTime() const; ///< Return the entry date time
   EType getType() const; ///< Return the message type
   QString getMessage() const; ///< Return the message
   QString toString() const; ///< Return the log entry as a string

private: // data members
   QDateTime dateTime_; ///< The timestamp of the log entry
   EType type_; ///< The entry type
   QString message_; ///< The message
};


typedef std::shared_ptr<DebugLogEntry> SpDebugLogEntry; ///< Type definition for shared pointer to DebugLogEntry
typedef std::deque<SpDebugLogEntry> DeqSpLogEntry; ///< Type definition for double ended queue of SPLogEntry


} // namespace xmilib


#endif // #ifndef XMILIB_DEBUG_LOG_ENTRY_H
