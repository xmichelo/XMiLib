/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of string related utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "StringUtils.h"


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


} // namespace xmilib
