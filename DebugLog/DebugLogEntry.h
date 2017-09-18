/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of debug log entry class
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__DEBUG__LOG__ENTRY__H
#define XMILIB__DEBUG__LOG__ENTRY__H


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
	DebugLogEntry(EType type, QString const& message); ///< Default constructor
	~DebugLogEntry() = default; ///< Default destructor
	QDateTime getDateTime() const; ///< Return the entry date time
   EType getType() const; ///< Return the message type
   QString getMessage() const; ///< Return the message
   QString toString() const; ///< Return the log entry as a string

private: // member functions
	DebugLogEntry(DebugLogEntry const&); ///< Disabled copy constructor
	DebugLogEntry& operator=(DebugLogEntry const&); ///< Disabled assignment operator

private: // data members
   QDateTime dateTime_; ///< The timestamp of the log entry
   EType type_; ///< The entry type
   QString message_; ///< The message
};


typedef std::shared_ptr<DebugLogEntry> SPDebugLogEntry; ///< Type definition for shared pointer to DebugLogEntry
typedef std::deque<SPDebugLogEntry> DeqSPLogEntry; ///< Type definition for double ended queue of SPLogEntry


} // namespace xmilib


#endif // #ifndef XMILIB__DEBUG__LOG__ENTRY__H
