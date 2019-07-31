/// \file
/// \author 
///
/// \brief Declaration of of CSV (comma-separated values) file I/O functions
/// 
/// For a description of the CSV file format see:
/// 
/// - Wikipedia: https://en.wikipedia.org/wiki/Comma-separated_values
/// - RFC 4180 https://tools.ietf.org/html/rfc4180
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#ifndef XMILIB_CSV_IO_H
#define XMILIB_CSV_IO_H


namespace xmilib {


bool loadCsvFile(QString const& path, QVector<QStringList>& outResult, QString& outErrorMsg); ///< \brief Load the content of a C
bool saveCsvFile(QString const& path ,QVector<QStringList> const& data, QString &outErrorMsg); ///< \brief Save data to a CSV file

} // namespace xmilib



#endif // #ifndef XMILIB_CSV_IO_H
