/// \file
/// \author 
///
/// \brief Implementation of of CSV file I/O functions
///  
/// Copyright (c) . All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information. 


#include "stdafx.h"
#include "CsvIO.h"
#include "Exception.h"


using namespace xmilib;


namespace {


QChar const kDoubleQuote = QChar('"'); ///< The double quote character.
QChar const kComma = QChar(','); ///< The comma character.
QChar const kNewLine = QChar('\n'); ///< The newline quote character.


//**********************************************************************************************************************
/// \brief An internal stucture used to parse CSV file.
//**********************************************************************************************************************
struct ParseInfo
{
   QTextStream stream; ///< The text stream.
   QChar currentChar; ///< The current character.
   QChar nextChar; ///< The next character.
   bool inQuotedSection { false }; ///< Are we currently parsing a quoted section.
   QVector<QStringList> result; ///< The current result of the parsing.
   QStringList currentRow; ///< The current row being parsed.
   QString currentString; ///< The current string being parsed.
};


}


namespace xmilib {


//**********************************************************************************************************************
/// \brief A single character from a text stream.
/// 
/// \param[in] stream The stream to read from.
/// \return The character read from the stream.
/// \return A null character if the end of the stream has been reached.
//**********************************************************************************************************************
QChar readChar(QTextStream& stream)
{
   QString const s = stream.read(1);
   return s.isEmpty() ? QChar() : s.front();
}


//**********************************************************************************************************************
/// \brief Process a double quote character.
/// \param[in] pi The parsing information structure.
//**********************************************************************************************************************
void processDoubleQuote(ParseInfo& pi)
{
   if (pi.nextChar == kDoubleQuote)
   {
      if (pi.inQuotedSection)
      {
         pi.currentString += kDoubleQuote;
         pi.nextChar = readChar(pi.stream);
      }
      else
         pi.inQuotedSection = true;
   }
   else
   {
      pi.inQuotedSection = !pi.inQuotedSection;
   }
}


//**********************************************************************************************************************
/// \brief Process a comma character.
/// \param[in] pi The parsing information structure.
//**********************************************************************************************************************
void processComma(ParseInfo& pi)
{
   if (pi.inQuotedSection)
   {
      pi.currentString += kComma;
      return;
   }
   pi.currentRow += pi.currentString;
   pi.currentString = QString();
}


//**********************************************************************************************************************
/// \brief Process a newline character.
/// \param[in] pi The parsing information structure.
//**********************************************************************************************************************
void processNewLine(ParseInfo& pi)
{
   if (pi.inQuotedSection)
   {
      pi.currentString += kNewLine;
      return;
   }
   pi.currentRow += pi.currentString;
   pi.result += pi.currentRow;
   pi.currentRow = QStringList();
   pi.currentString = QString();
}


//**********************************************************************************************************************
/// \param[in] csvData The loaded CSV data.
/// \param[out] outErrorMsg If the function returns false this variables hold a description of the error on exit.
/// \return true if and only if the loaded CSV data is valid.
//**********************************************************************************************************************
bool isLoadedCsvContentValid(QVector<QStringList> const& csvData, QString* outErrorMsg)
{
   try
   {
      if (csvData.isEmpty())
         throw Exception("The CSV file is empty.");
      qsizetype const width = csvData.front().size();
      for (QVector<QStringList>::const_iterator it = csvData.begin() + 1; it != csvData.end(); ++it)
         if (it->size() != width)
            throw Exception("Not all rows in the CSV file have the same number of columns.");
      return true;
   }
   catch (Exception const& e)
   {
      if (outErrorMsg)
         *outErrorMsg = e.qwhat();
      return false;
   }
}
      

//**********************************************************************************************************************
/// \param[in] path The path of the file to parse.
/// \param[out] outResult The loaded content.
/// \param[out] outErrorMsg If the function returns false this variables hold a description of the error on exit.
/// \return true if and only if the file was successfully parsed.
//**********************************************************************************************************************
bool loadCsvFile(QString const& path, QVector<QStringList>& outResult, QString* outErrorMsg)
{
   outResult.clear();
   QFile file(path);
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      if (outErrorMsg)
         *outErrorMsg = QString("Could not open file '%1' for reading.").arg(path);
      return false;
   }
   ParseInfo pi;
   pi.stream.setDevice(&file);
   pi.stream.setEncoding(QStringConverter::Utf8);
   pi.currentChar = readChar(pi.stream);
   pi.nextChar = readChar(pi.stream);

   while (! pi.currentChar.isNull())
   {
      // process double quotes
      if (kDoubleQuote == pi.currentChar)
         processDoubleQuote(pi);
      else if (kComma == pi.currentChar)
         processComma(pi);
      else if (kNewLine == pi.currentChar)
         processNewLine(pi);
      else
         pi.currentString += pi.currentChar;

      pi.currentChar = pi.nextChar;
      pi.nextChar = readChar(pi.stream);
   }

   if (!pi.currentString.trimmed().isEmpty())
      pi.currentRow += pi.currentString;

   if (!pi.currentRow.isEmpty())
      pi.result += pi.currentRow;

   if (!isLoadedCsvContentValid(pi.result, outErrorMsg))
      return false;

   outResult = pi.result;
   return true;
}


//**********************************************************************************************************************
/// \param[in] path The path of the file to parse.
/// \param[out] data The data to write.
/// \param[out] outErrorMsg If the function returns false this variables hold a description of the error on exit.
/// \return true if and only if the file was successfully saved.
//**********************************************************************************************************************
bool saveCsvFile(QString const& path, QVector<QStringList> const& data, QString* outErrorMsg)
{
   QString const writeErrorMsg(QObject::tr("An error occured while writing data to'%1'.")
      .arg(QDir::toNativeSeparators(path)));
   QByteArray const comma = QString(",").toUtf8();
   QByteArray const newLine = QString("\n").toUtf8();
   try
   {
      QFile file(path);
      if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         throw Exception(QObject::tr("Could not open file '%1' for writing.").arg(QDir::toNativeSeparators(path)));
      for (QVector<QStringList>::const_iterator recordIt = data.begin(); recordIt != data.end(); ++recordIt)
      {
         QStringList const& record = *recordIt;
         for (QStringList::const_iterator fieldIt = record.begin(); fieldIt != record.end(); ++fieldIt)
         {
            QByteArray utf8 = ('"' + QString(*fieldIt).replace("\"", "\"\"") + '"').toUtf8();
            if (utf8.size() != file.write(utf8))
               throw Exception(writeErrorMsg);
            if (fieldIt + 1 != record.end())
               if (comma.size() != file.write(comma))
                  throw Exception(writeErrorMsg);
         }
         if ((recordIt + 1 != data.end()))
            if (comma.size() != file.write(newLine))
               throw Exception(writeErrorMsg);
      }
      return true;
   }
   catch (Exception const& e)
   {
      if (outErrorMsg)
         *outErrorMsg = e.qwhat();
      return false;
   }
}


} // namespace xmilib
