/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of style sheet editor for Qt applications
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#include "stdafx.h"
#include "StyleSheetEditor.h"
#include "ui_StyleSheetEditor.h"


namespace {
   QString const kDefaultStyleSheetFileName = "style.css"; // The file name for the style sheet
}


namespace xmilib {


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
StyleSheetEditor::StyleSheetEditor(QWidget* parent)
   : QWidget(parent)
   , ui_(new Ui::StyleSheetEditor())
{
   ui_->setupUi(this);
   this->setWindowFlags(this->windowFlags() | Qt::Window);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
StyleSheetEditor::~StyleSheetEditor()
{
   delete ui_;
}


//**********************************************************************************************************************
/// \return True if and only if a stylesheet file was found an loaded
//**********************************************************************************************************************
bool StyleSheetEditor::loadStyleSheet() const
{
   QFile file(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
      .absoluteFilePath(kDefaultStyleSheetFileName));
   if ((!file.exists()) || (!file.open(QIODevice::ReadOnly)))
      return false;
   ui_->edit->setPlainText(QString::fromUtf8(file.readAll()));
   this->applyStyleSheet();
   return true;
}


//**********************************************************************************************************************
/// \return true if and only if the stylesheet was successfully saved
//**********************************************************************************************************************
bool StyleSheetEditor::saveStyleSheet() const
{
   QDir appDataDir = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
   if (!appDataDir.exists() && (!QDir().mkpath(appDataDir.absolutePath())))
      return false;
   QFile file(appDataDir.absoluteFilePath(kDefaultStyleSheetFileName));
   if (!file.open(QIODevice::WriteOnly))
      return false;
   QByteArray const data = ui_->edit->toPlainText().toUtf8();
   return data.size() == file.write(data);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::applyStyleSheet() const
{
   dynamic_cast<QApplication *>(QCoreApplication::instance())->setStyleSheet(
      (originalStylesheet_ + "\n\n"+ ui_->edit->toPlainText()).trimmed());
}


//**********************************************************************************************************************
/// \param[in] originalStyleSheet The original style sheet to be preprended to the editor's style sheet
//**********************************************************************************************************************
void StyleSheetEditor::setOriginalStyleSheet(QString const& originalStyleSheet)
{
   originalStylesheet_ = originalStyleSheet.trimmed();
   this->applyStyleSheet();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionApply() const
{
   // ReSharper disable once CppExpressionWithoutSideEffects
   this->saveStyleSheet();
   this->applyStyleSheet();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionOk()
{
   this->onActionApply();
   this->close();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionCancel()
{
   this->close();
}


} // namespace xmilib
