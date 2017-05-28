/// \file
/// \author Xavier Michelon
///
/// \brief Declaration of style sheet editor for Qt applications


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
public: // static data members
   static QString kStyleSheetFileName; ///< The name of the file where the style sheet is stored in the application data folder

public: // static member function
   static void loadAndApplyStyleSheet(); ///< Load the theme from the default theme file and applies it to the application

public: // member functions
	StyleSheetEditor(QWidget* parent = nullptr); ///< Default constructor
	virtual ~StyleSheetEditor() override = default; ///< Default destructor

private: // member functions
	StyleSheetEditor(StyleSheetEditor const&); ///< Disabled copy constructor
	StyleSheetEditor& operator=(StyleSheetEditor const&); ///< Disabled assignment operator
   void saveAndApplyTheme() const; ///< Apply the theme
   void saveTheme() const; ///< Save the theme

private slots:
   void onActionApply(); ///< Slot for the 'Apply' action
   void onActionOk(); ///< Slot for the 'Close' action
   void onActionCancel(); ///< Slot for the 'Cancel' action


private: // data members
   std::unique_ptr<Ui::StyleSheetEditor> ui_; ///< The GUI for the window
};


} // namespace xmilib


#endif // #ifndef XMILIB__STYLE__SHEET__EDITOR__H
