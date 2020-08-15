/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of string related utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "StringUtils.h"
#include "Exception.h"


namespace xmilib {


//**********************************************************************************************************************
/// The letters in the results are in lower case, and numbers below sixteen are padded to the left with a zero
///
/// \param[in] byte The byte
/// \return The 2 characters representation of the byte
//**********************************************************************************************************************
QString byteToHexString(char byte)
{
   return QString("%1").arg(quint8(byte), 2, 16, QChar('0'));
}


//**********************************************************************************************************************
/// \param[in] array The byte array
/// \param[in] separator The separator to insert between bytes
/// \param[in] bytesPerLine The number of bytes to display per line. If the value is 0 or below, The byte array is 
/// returned on a single line
/// \return A string containing the hexadecimal representation of the byte array
//**********************************************************************************************************************
QString byteArrayToHexString(QByteArray const& array, QString const& separator, qint32 bytesPerLine)
{
   if (array.isEmpty())
      return QString();
   QString result = byteToHexString(array[0]);
   for (qint32 i = 1; i < array.size(); ++i)
      result += (((bytesPerLine > 0) && (0 == i % bytesPerLine)) ? "\n" : separator) + byteToHexString(array[i]);
   return result;
}


//**********************************************************************************************************************
/// \return "true" if value is true
/// \return "false" if value is false
//**********************************************************************************************************************
QString boolToString(bool value)
{
   return value ? "true" : "false";
}


//**********************************************************************************************************************
/// \param[in] stringList The stringList.
/// \return The JSON document containing the array.
//**********************************************************************************************************************
QJsonDocument stringListToJsonDocument(QStringList const& stringList)
{
   QJsonArray array;
   for (QString const& str: stringList)
      array.append(str);
   return QJsonDocument(array);
}


//**********************************************************************************************************************
/// \param[in] doc The JSON document to read from.
/// \param[out] outStringList The string list read from the JSON document.
/// \param[out] outErrorMessage message if the function returns false and this parameter is not null, it contains a 
/// description of the error on exit.
/// \return true if and only if the string list was successfully loaded
//**********************************************************************************************************************
bool jsonDocumentToStringList(QJsonDocument const& doc, QStringList& outStringList, 
   QString* outErrorMessage)
{
   try
   {
      if (!doc.isArray())
         throw Exception("The JSON document is not an array");
      QJsonArray array = doc.array();
      for (QJsonValueRef const value: array)
      {
         if (!value.isString())
            throw Exception("The JSON document does not contain a valid string array");
         outStringList.append(value.toString());
      }
      return true;
   }
   catch (Exception const& e)
   {
      if (outErrorMessage)
         *outErrorMessage = e.qwhat();
      return false;
   }
}


//**********************************************************************************************************************
/// \param[in] stringList The string list.
/// \param[in] filePath The path of the file to write to.
/// \param[out] outErrorMessage message if the function returns false and this parameter is not null, it contains a 
/// description of the error on exit.
//**********************************************************************************************************************
bool saveStringListToJsonFile(QStringList const& stringList, QString const& filePath,
   QString* outErrorMessage)
{
   try
   {
      QJsonDocument const doc = stringListToJsonDocument(stringList);
      QFile file(filePath);
      if (!file.open(QIODevice::WriteOnly))
         throw Exception("The input file could not be opened.");
      QByteArray const data = doc.toJson();
      if (data.size() != file.write(data))
         throw Exception("An error occurred while trying to write file.");
      return true;
   }
   catch (Exception const& e)
   {
      if (outErrorMessage)
         *outErrorMessage = e.qwhat();
      return false;
   }
}


//**********************************************************************************************************************
/// \param[in] filePath The path of the file to read from.
/// \param[out] outStringList The string list read from the JSON document.
/// \param[out] outErrorMessage message if the function returns false and this parameter is not null, it contains a 
/// description of the error on exit.
/// \return true if and only if the string list was successfully loaded
//**********************************************************************************************************************
bool loadStringListFromJsonFile(QString const& filePath, QStringList& outStringList,
   QString* outErrorMessage)
{
   try
   {
      QFile file(filePath);
      if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         throw Exception("The output file could not be opened.");
      QJsonDocument const doc = QJsonDocument::fromJson(file.readAll());
      if (doc.isNull())
         throw Exception("The input file is not a valid JSON file.");
      return jsonDocumentToStringList(doc, outStringList, outErrorMessage);
   }
   catch (Exception const& e)
   {
      if (outErrorMessage)
         *outErrorMessage = e.qwhat();
      return false;
   }}


} // namespace xmilib
