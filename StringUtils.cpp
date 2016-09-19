/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of string related utility functions


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


} // namespace xmilib
