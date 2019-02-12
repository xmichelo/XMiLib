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
QString boolToString(bool value); ///< Returns a string representing the given value
QJsonDocument stringListToJsonDocument(QStringList const& stringList, QString const& arrayName); ///< Export a string list to a JSON document
bool jsonDocumentToStringList(QJsonDocument const& doc, QString const& arrayName, QStringList& outStringList, QString* outErrorMessage); ///< Read a string list to a JSON document.
bool loadStringListFromJsonFile(QString const& filePath, QString const& arrayName, QStringList& outStringList, QString* outErrorMessage); ///< Load a string list from a JSON document.
bool saveStringListToJsonFile(QStringList const& stringList, QString const& arrayName, QString const& filePath, QString* outErrorMessage = nullptr); ///< Save a string list to a JSON file.

} // namespace xmilib


#endif // #ifndef XMILIB_STRING_UTILS_H