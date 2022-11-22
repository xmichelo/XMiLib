/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of file related utility function
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  



#include "stdafx.h"
#include "FileUtils.h"
#include "RandomNumberGenerator.h"


namespace {


qint32 kTempDirNameLength = 16; ///< The length of the name of temporary folders
qint32 kMaxRetryCount = 1000; ///< The number of trial to perform when creating random files or folders


xmilib::RandomNumberGenerator &nameRng();


//****************************************************************************************************************************************************
/// \return A reference to the random number generator used to create random file names
//****************************************************************************************************************************************************
xmilib::RandomNumberGenerator &nameRng() {
    static xmilib::RandomNumberGenerator instance(0, 15);
    return instance;
}


} // anonymous namespace


namespace xmilib {


//****************************************************************************************************************************************************
/// \param[in] length the length of the random portion of the file (i.e. without the extension and prefix)
/// \param[in] prefix The prefix that starts the file name. This value can be null or empty
/// \param[in] extension The file extension, without leading '.'
/// \return A random file name with the specified base name length and extension
//****************************************************************************************************************************************************
QString getRandomFileName(qint32 length, QString const &prefix, QString const &extension) {
    QString result = prefix;
    for (int i = 0; i < length; ++i)
        result += QString("%1").arg(nameRng().get(), 1, 16);
    return extension.isEmpty() ? result : result + "." + extension;
}


//****************************************************************************************************************************************************
/// \param[in] prefix The prefix that starts the file name. This value can be null or empty
/// \param[in] extension The file extension, without the leading '.'
/// \return The full path of an non-existing file in the user temporary folder
////**********************************************************************************************************************
QString getTempFilePath(QString const &prefix, QString const &extension) {
    for (qint32 retryCount = 0; retryCount < kMaxRetryCount; ++retryCount) {
        QString path = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation))
            .absoluteFilePath(getRandomFileName(16, prefix, extension));
        if (!QFileInfo(path).exists())
            return path;
    }
    return QString();
}


//****************************************************************************************************************************************************
/// \return The path of the newly created folder
/// \return A null string if the temporary folder could not be created
//****************************************************************************************************************************************************
QString createTempDir() {
    qint32 retryCount = 0;
    while (retryCount++ < kMaxRetryCount) {
        QString path = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation))
            .absoluteFilePath(getRandomFileName(kTempDirNameLength));
        QFileInfo fileInfo(path);
        if ((fileInfo.exists()) || (!QDir().mkpath(path)))
            continue;
        return path;
    }
    return QString();
}


//****************************************************************************************************************************************************
/// \param[out] outFile The created file, open for writing
/// \param[in] prefix The prefix that starts the file name. This value can be null or empty
/// \param[in] extension The file extension, without the leading '.'
/// \param[in] textMode Should the file be open in text mode
/// \return The absolute path of the created file
//****************************************************************************************************************************************************
QString createTempFile(QFile &outFile, QString const &prefix, QString const &extension, bool textMode) {
    qint32 retryCount = 0;
    while (retryCount++ < kMaxRetryCount) {
        QString path = QDir(QStandardPaths::writableLocation(QStandardPaths::TempLocation))
            .absoluteFilePath(getRandomFileName(16, prefix, extension));
        if (path.isEmpty() || (QFileInfo(path).exists()))
            continue;
        outFile.close();
        outFile.setFileName(path);

        if (!outFile.open(textMode ? (QIODevice::WriteOnly | QIODevice::Text) : QIODevice::WriteOnly))
            continue;
        return path;
    }
    return QString();
}


} // namespace xmilib