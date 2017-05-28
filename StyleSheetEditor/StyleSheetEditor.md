# Style Sheet Editor

## Introduction
The style sheet editor is a Qt widget allowing to edit the style sheet for a Qt application in real time. [Qt style sheets](http://doc.qt.io/qt-5/stylesheet.html) give developers the opportunity to completely modify the appareance of Qt GUI applications.

## Usage
The StyleSheetEditor class is easy to use. Simply instanciate the class and show it. 

~~~~cpp
xmilib::StyleSheetEditor* editor = new xmilib::StyleSheetEditor(this);
editor->show();
~~~~

When pressing ``OK`` (or ``Apply``), the stylesheet typed in the editor is applied to the entire application, using ``qApp->setStyleSheet()``, and it is also saved to the application data folder.

It is important to notice that the application data folder depends on the application name and organization registered using ``QApplication::setApplicationName()`` and ``QApplication::setOrganizationName()`` during application initialization. 

To load the saved style sheet, use the static function ````xmilib::StyleSheetEditor::loadAndApplyStyleSheet()````. Here is simple example of ````main()```` function:

~~~~cpp
int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   a.setApplicationName("Style Sheet Editor Test");
   a.setOrganizationName("x-mi.com");
   xmilib::StyleSheetEditor::loadAndApplyStyleSheet();
   MainWindow w;
   w.show();
   return a.exec();
}
~~~~

## Test application
A test application showing how to use the StyleSheetEditor widget is provided in the subfolder ``TestApps/StyleSheetEditorTest``.
