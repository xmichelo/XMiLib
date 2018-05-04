/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of test functions for the XMiLib file utility functions
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "XMiLibTest.h"
#include <XMiLib/RandomNumberGenerator.h>
#include <XMiLib/FileUtils.h>


using namespace xmilib;


namespace {
   QString const kFileNamePrefix = "prefix_"; ///< The prefix for temp file names
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::fileUtils_getRandomFileName()
{
   try 
   {
      RandomNumberGenerator rng(1, 100);
      QRegularExpression hexaStringRegExp(R"(^[0-9a-z]+$)");

      for (qint32 i = 0; i < 100; ++i)
      {
         bool const usePrefix = i % 2;
         qint32 const prefixSize = usePrefix ? kFileNamePrefix.size() : 0;

         // we use the generator to generate an extension.
         qint32 const extLength = rng.get();
         QString const ext = getRandomFileName(extLength);
         QVERIFY2(ext.length() == extLength, "The generated extension does not have the appropriate length.");
         QVERIFY2(hexaStringRegExp.match(ext).hasMatch(), "The generated extension is not valid.");

         // then we generate another name with an extension
         qint32 const baseLength = rng.get();
         QString const fileName = getRandomFileName(baseLength, usePrefix ? kFileNamePrefix : QString(), ext);
         QVERIFY2(fileName.length() == 1 + extLength + baseLength + prefixSize,  
            "The generated file name does not have the appropriate length.");
         QRegularExpressionMatch match = QRegularExpression(QString(R"(^((.{%1})([0-9a-z]+))\.([0-9a-z]+)$)")
            .arg(prefixSize)).match(fileName);
         QVERIFY2(match.hasMatch(), "The generated file name is invalid.");
         QVERIFY2(match.captured(4) == ext, "The generated file name does not have the expected extension.");
         QString const baseName = match.captured(1);
         QVERIFY2(baseName.length() == baseLength + prefixSize , 
            "The generated file name does not have the expected base name.");
         QVERIFY2(QRegularExpression(QString(R"(^.{%1}[0-9a-z]+$)").arg(prefixSize)).match(baseName).hasMatch(), 
            "The generated base name is not valid.");
         if (usePrefix)
            QVERIFY2(fileName.startsWith(kFileNamePrefix), "The file name does not have the expected prefix.");
      }
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception.");
   }
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::fileUtils_createTempDir()
{
   try
   {
      for (qint32 i = 0; i < 100; ++i)
      {
         QString path = createTempDir();
         QVERIFY2(!path.isEmpty(), "The function returned an empty path.");
         QFileInfo fileInfo(path);
         QVERIFY2(fileInfo.exists(), "The created folder does not exist.");
         QVERIFY2(fileInfo.isDir(), "The created folder is not a folder.");
         QDir dir(path);
         QVERIFY2(dir.removeRecursively(), "The created folder could not be removed");
         fileInfo.refresh();
         QVERIFY2(!fileInfo.exists(), "The created folder could not be deleted.");
      }
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception.");
   }
   
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void XMiLibTest::fileUtils_createTempFile()
{
   try
   {
      RandomNumberGenerator rng(0, 255);
      for (qint32 i = 0; i < 100; ++i)
      {
         QFile file;
         QString path = createTempFile(file, QString(), "tmp", false);
         QVERIFY2(!path.isEmpty(), "The file could not be created.");
         QVERIFY2(file.isOpen(), "The file is invalid");
         qint32 const fileSize = rng.get() + 1;
         QByteArray const data(fileSize, char(rng.get()));
         QVERIFY2(fileSize == file.write(data), "An error occurred while writing to file");
         file.close();
         QFileInfo fileInfo(path);
         QVERIFY2(fileInfo.size() == fileSize, "The file is not of the appropriate size.");
         QVERIFY2(file.remove(), "The file could not be removed.");
         fileInfo.refresh();
         QVERIFY2(!fileInfo.exists(), "The file was not properly removed");

      }
   }
   catch (...)
   {
      QVERIFY2(false, "The function threw an exception.");
   }
}

