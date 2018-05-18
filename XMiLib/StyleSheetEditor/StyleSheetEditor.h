/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of style sheet editor for Qt applications
///  
/// Copyright (c) Xavier Michelon. All rights reserved.  
/// Licensed under the MIT License. See LICENSE file in the project root for full license information.  


#ifndef XMILIB_STYLE_SHEET_EDITOR_H
#define XMILIB_STYLE_SHEET_EDITOR_H


// ReSharper disable once CppInconsistentNaming
namespace Ui { class StyleSheetEditor; }


namespace xmilib {


//**********************************************************************************************************************
/// \brief Class for the Qt style sheet editor window
//**********************************************************************************************************************
class StyleSheetEditor: public QWidget
{
   Q_OBJECT
public: // member function
   explicit StyleSheetEditor(QWidget* parent = nullptr); ///< Default constructor
	StyleSheetEditor(StyleSheetEditor const&) = delete; ///< Disabled copy constructor
	StyleSheetEditor(StyleSheetEditor&&) = delete; ///< Disabled move copy constructor
	~StyleSheetEditor() override; ///< Default destructor
	StyleSheetEditor& operator=(StyleSheetEditor const&) = delete; ///< Disabled assignment operator
	StyleSheetEditor& operator=(StyleSheetEditor&&) = delete; ///< Disabled move assignment operator
   bool loadStyleSheet() const; ///< Load a style sheet from file
   bool saveStyleSheet() const; ///< Save the style sheet
   void applyStyleSheet() const; ///< Apply the style sheet from the editor
   void setOriginalStyleSheet(QString const& originalStyleSheet); ///< Set the original stylesheet

private slots:
   void onActionApply() const; ///< Slot for the 'Apply' action
   void onActionOk(); ///< Slot for the 'Close' action
   void onActionCancel(); ///< Slot for the 'Cancel' action


private: // data members
   Ui::StyleSheetEditor* ui_; ///< The GUI for the window
   QString originalStylesheet_; ///< The original style sheet
};


} // namespace xmilib


#endif // #ifndef XMILIB_STYLE_SHEET_EDITOR_H
