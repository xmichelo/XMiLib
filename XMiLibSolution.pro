TEMPLATE = subdirs

SUBDIRS += \
   XMiLibGuiTest \
   XMiLibTest \
   XMiLib

XMiLibGuiTest.subdir = Test/XMiLibGuiTest
XMiLibTest.subdir = Test/XMiLibTest
XMiLib.subdir = XMiLib


XMiLibGuiTest.depends = XMiLib
XMiLibTest.depends = XMiLib


