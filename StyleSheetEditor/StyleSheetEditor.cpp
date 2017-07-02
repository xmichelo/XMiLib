/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of style sheet editor for Qt applications


#include "stdafx.h"
#include "StyleSheetEditor.h"
#include "ui_StyleSheetEditor.h"


namespace xmilib {


QString StyleSheetEditor::kDefaultStyleSheetFileName = "style.css";


//**********************************************************************************************************************
/// \param[in] parent The parent widget of the window
//**********************************************************************************************************************
StyleSheetEditor::StyleSheetEditor(QWidget* parent)
   : QWidget(parent)
   , ui_(std::make_unique<Ui::StyleSheetEditor>())
{
   ui_->setupUi(this);
   this->setWindowFlags(this->windowFlags() | Qt::Window);
}


//**********************************************************************************************************************
/// \param[in] filePath The path of the style sheet file to load. If the variable is empty, the file is saved
/// the default location in the application folder
/// \return True if and only if a 
//**********************************************************************************************************************
bool StyleSheetEditor::loadStyleSheet()
{
   QFile file(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
      .absoluteFilePath(StyleSheetEditor::kDefaultStyleSheetFileName));
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
   if (!appDataDir.exists())
      QDir().mkpath(appDataDir.absolutePath());
   QFile file(appDataDir.absoluteFilePath(kDefaultStyleSheetFileName));
   if (!file.open(QIODevice::WriteOnly))
      return false;
   QByteArray const data = ui_->edit->toPlainText().toUtf8();
   return data.size() == file.write(data);
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::applyStyleSheet()
{
   qApp->setStyleSheet(ui_->edit->toPlainText());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionApply()
{
   this->saveStyleSheet();
   this->applyStyleSheet();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionOk()
{
   this->saveStyleSheet();
   this->applyStyleSheet();
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
