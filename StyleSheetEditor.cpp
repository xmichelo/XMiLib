/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of style sheet editor for Qt applications


#include "stdafx.h"
#include "StyleSheetEditor.h"
#include "ui_StyleSheetEditor.h"


namespace xmilib {


QString StyleSheetEditor::kStyleSheetFileName = "style.css";


//**********************************************************************************************************************
/// It is safe to call this function even if no style sheet file is present in the application data folder
//**********************************************************************************************************************
void StyleSheetEditor::loadAndApplyStyleSheet()
{
   QFile file(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation))
      .absoluteFilePath(StyleSheetEditor::kStyleSheetFileName));
   if (!file.open(QIODevice::ReadOnly))
      return;
   qApp->setStyleSheet(file.readAll());
}


//**********************************************************************************************************************
/// \param[in] parent
//**********************************************************************************************************************
StyleSheetEditor::StyleSheetEditor(QWidget* parent)
   : QWidget(parent)
   , ui_(std::make_unique<Ui::StyleSheetEditor>())
{
   ui_->setupUi(this);
   this->setWindowFlags(this->windowFlags() | Qt::Window);
   ui_->edit->setPlainText(qApp->styleSheet());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::saveAndApplyTheme() const
{
   qApp->setStyleSheet(ui_->edit->toPlainText());
   this->saveTheme();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::saveTheme() const
{
   QDir dir(QStandardPaths::writableLocation(QStandardPaths::DataLocation));
   if (!dir.exists())
      QDir().mkpath(dir.absolutePath());
   QFile file(dir.absoluteFilePath(kStyleSheetFileName));
   if (file.open(QIODevice::WriteOnly))
      file.write(ui_->edit->toPlainText().toLocal8Bit());
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionApply()
{
   this->saveAndApplyTheme();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionOk()
{
   this->saveAndApplyTheme();
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
