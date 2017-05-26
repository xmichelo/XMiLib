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
// 
//**********************************************************************************************************************
StyleSheetEditor::StyleSheetEditor()
   : QWidget(nullptr)
   , ui_(std::make_unique<Ui::StyleSheetEditor>())
{
    ui_->setupUi(this);
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
   qDebug() << QString("%1()").arg(__FUNCTION__);
   this->saveAndApplyTheme();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionOk()
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   this->saveAndApplyTheme();
   this->close();
}


//**********************************************************************************************************************
// 
//**********************************************************************************************************************
void StyleSheetEditor::onActionCancel()
{
   qDebug() << QString("%1()").arg(__FUNCTION__);
   this->close();
}


} // namespace xmilib
