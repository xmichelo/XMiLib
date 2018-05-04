TEMPLATE = app
TARGET = XMiLibTest
QT += core gui testlib
CONFIG += precompile_header
PRECOMPILED_HEADER = stdafx.h

include(XMiLibTest.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../XMiLib/release/ -lXMiLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../XMiLib/debug/ -lXMiLib
else:unix: LIBS += -L$$OUT_PWD/../../XMiLib/ -lXMiLib

INCLUDEPATH += $$PWD/../..
DEPENDPATH += $$PWD/../..

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../XMiLib/release/libXMiLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../XMiLib/debug/libXMiLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../XMiLib/release/XMiLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../XMiLib/debug/XMiLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../XMiLib/libXMiLib.a
