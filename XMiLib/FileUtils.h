/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of file related utility function
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__FILE__UTILS__H
#define XMILIB__FILE__UTILS__H


namespace xmilib {


QString getRandomFileName(qint32 length = 16, QString const& prefix = QString(), QString const& extension = QString()); ///< Create a temporary file name
QString createTempDir(); ///< Create a new directory with a random name in the user temporary folder
QString createTempFile(QFile& outFile, QString const& prefix = QString(), QString const& extension = QString(), 
   bool textMode = false); ///< Create a temporary file in the temporary folder and open it for writing

} // namespace xmilib


#endif // #ifndef XMILIB__FILE__UTILS__H