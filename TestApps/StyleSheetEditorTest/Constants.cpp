/// \file
/// \author Xavier Michelon
///
/// \brief Implementation of application wide constant


#include "stdafx.h"
#include "Constants.h"


QString const kSampleStyleSheet = R"(QWidget {
   color: #ffffff;
   background-color: #444444;
   font-family: 'Segoe UI';
   font-size: 9pt;
   font-weight: normal;
}

QToolBar {
   border: none;
   border-top: 1px solid #444444;
}

QPlainTextEdit {
  font-family: Consolas; 
  font-size: 10pt;
}

QAbstractScrollArea {
  border: 1px solid #666666;
  background-color: #555555;
}

QPushButton {
   min-width: 50px;
   padding: 6px 10px 6px 10px;
   border: 1px solid #777777;
   background-color: #555555;
}

QPushButton::hover {
   background-color: #666666;
}

QPushButton::pressed {
   background-color: #777777;
}

QPushButton::disabled {
   color: #777777;
   background-color: #555555;
   border-color: #333333;
}


QToolButton::hover {
   border: none;
   background-color: #555555;
}


QToolButton::pressed {
   background-color: #666666;
}

QToolButton::disabled {
   color: #666666;
}

QMenuBar:item::selected {
background-color: #444444;
}

QMenuBar:item::disabled {
color: #666666;
}

QMenu {
padding: 0px;
}

QMenu::separator {
   height: 1px;
   background-color: #555555;
   margin: 4px 5px 4px 15px;
}

QMenu:item::selected {
background-color: #333333;
}

QMenu:item::disabled {
   color: #6b6b6b;
}

QScrollBar {
   border: none;
   background: #666666;
   margin: 0px;
}

QScrollBar:vertical {
   width: 15px;
}

QScrollBar::handle {
   background: #888888;
   border-radius: 7px;
}

QScrollBar:horizontal {
   height: 15px;
}

QScrollBar::handle:vertical {
   min-height: 20px;
}

QScrollBar::handle:horizontal {
   min-width: 20px;
}

QScrollBar::add-line, QScrollBar::sub-line, QScrollBar::add-page, QScrollBar::sub-page, 
QScrollBar::up-arrow, QScrollBar::down-arrow, QScrollBar::left-arrow, QScrollBar::right-arrow {
   border: none;
   background: none;
}
)";
