/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of string related utility functions


#ifndef XMILIB__STRING__UTILS__H
#define XMILIB__STRING__UTILS__H


namespace xmilib {


QString byteToHexString(char byte); ///< Returns a string containing the two characters hexadecimal representation of a byte
QString byteArrayToHexString(QByteArray const& array, QString const& separator = QString(), qint32 bytesPerLine = 0); ///< Returns a string containing the hexadecimal representation of a byte array


} // namespace xmilib


#endif // #ifndef XMILIB__STRING__UTILS__H