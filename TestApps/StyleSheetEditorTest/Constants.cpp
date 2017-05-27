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
   border: 1px solid #444444;
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

QScrollBar:vertical {
     border: none;
     background: #666666;
     width: 15px;
     margin: 15px 0 15px 0;
 }

 QScrollBar::handle:vertical {
     background: #aaaaaa;
     min-height: 20px;
 }

 QScrollBar::add-line:vertical {
     border: none;
     background: #444444;
     height: 15px;
     subcontrol-position: bottom;
     subcontrol-origin: margin;
 }

 QScrollBar::sub-line:vertical {
     border: none;
     background: #444444;
     height: 15px;
     subcontrol-position: top;
     subcontrol-origin: margin;
 }
 QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {
     border: none;
     width: 3px;
     height: 3px;
     background: #aaaaaa;
 }

 QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
     background: none;
 }

QScrollBar:horizontal {
     border: none;
     background-color: #666666;
     height: 15px;
     margin: 0px 15px 0px 15px;
 }
 QScrollBar::handle:horizontal {
     background-color: #aaaaaa;
     min-height: 20px;
 }
 QScrollBar::add-line:horizontal {
     border: none;
     background: #444444;
     width: 15px;
     subcontrol-position: right;
     subcontrol-origin: margin;
 }

 QScrollBar::sub-line:horizontal {
     border: none;
     background: #444444;
     width: 15px;
     subcontrol-position: left;
     subcontrol-origin: margin;
 }
 QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {
     border: none;
     width: 3px;
     height: 3px;
     background: #aaaaaa;
 }

 QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
     background: none;
 }
)";
