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
   static QString kDefaultStyleSheetFileName; ///< The default name for the style sheet file

public: // static member function
   bool loadStyleSheet(); ///< Load a style sheet from file
   bool saveStyleSheet() const; ///< Save the style sheet
   void applyStyleSheet(); ///< Apply the style sheet from the editor

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
};


} // namespace xmilib


#endif // #ifndef XMILIB__STYLE__SHEET__EDITOR__H
