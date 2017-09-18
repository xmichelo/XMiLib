/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of style sheet editor for Qt applications
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB__STYLE__SHEET__EDITOR__H
#define XMILIB__STYLE__SHEET__EDITOR__H


#include <memory>


namespace Ui { class StyleSheetEditor; };


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for the Qt style sheet editor window
//**********************************************************************************************************************
class StyleSheetEditor: public QWidget
{
   Q_OBJECT
public: // member function
   bool loadStyleSheet(); ///< Load a style sheet from file
   bool saveStyleSheet() const; ///< Save the style sheet
   void applyStyleSheet(); ///< Apply the style sheet from the editor
   void setOriginalStyleSheet(QString const& originalStyleSheet); ///< Set the original stylesheet

public: // member functions
	StyleSheetEditor(QWidget* parent = nullptr); ///< Default constructor
	virtual ~StyleSheetEditor() override = default; ///< Default destructor

private: // member functions
	StyleSheetEditor(StyleSheetEditor const&); ///< Disabled copy constructor
	StyleSheetEditor& operator=(StyleSheetEditor const&); ///< Disabled assignment operator

private slots:
   void onActionApply(); ///< Slot for the 'Apply' action
   void onActionOk(); ///< Slot for the 'Close' action
   void onActionCancel(); ///< Slot for the 'Cancel' action


private: // data members
   std::unique_ptr<Ui::StyleSheetEditor> ui_; ///< The GUI for the window
   QString originalStylesheet_; ///< The original style sheet
};


} // namespace xmilib


#endif // #ifndef XMILIB__STYLE__SHEET__EDITOR__H
