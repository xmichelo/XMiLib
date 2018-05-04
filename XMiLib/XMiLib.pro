TEMPLATE = lib
TARGET = XMiLib
#DESTDIR = ../_build/Win32/Release
QT += core gui widgets
CONFIG += staticlib c++14
#DEFINES += XMILIB_LIB QT_WIDGETS_LIB
#INCLUDEPATH += ./GeneratedFiles/$(ConfigurationName) \
#    ./GeneratedFiles \
#    . \
#    ./DebugLog \
#    ./ThreadedOperation
PRECOMPILED_HEADER = stdafx.h
#DEPENDPATH += .
#MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
#OBJECTS_DIR += release
#UI_DIR += ./GeneratedFiles
#RCC_DIR += ./GeneratedFiles
include(XMiLib.pri)
#TRANSLATIONS += Translations/xmilib_fr.ts
