/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of string related utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_STRING_UTILS_H
#define XMILIB_STRING_UTILS_H


namespace xmilib {


QString byteToHexString(char byte); ///< Returns a string containing the two characters hexadecimal representation of a byte
QString byteArrayToHexString(QByteArray const& array, QString const& separator = QString(), qint32 bytesPerLine = 0); ///< Returns a string containing the hexadecimal representation of a byte array


} // namespace xmilib


#endif // #ifndef XMILIB_STRING_UTILS_H