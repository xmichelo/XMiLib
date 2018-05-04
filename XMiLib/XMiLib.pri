HEADERS += ./FileUtils.h \
   ./SystemUtils.h \
   ./Exception.h \
   ./RandomNumberGenerator.h \
   ./stdafx.h \
   ./StringUtils.h \
   ./StyleSheetEditor/StyleSheetEditor.h \
   ./DebugLog/DebugLogEntry.h \
   ./DebugLog/DebugLog.h \
   ./DebugLog/DebugLogWindow.h \
   ./DebugLog/DebugLogFilterProxyModel.h \
   ./ThreadedOperation/ThreadedOperationDialog.h \
   ./ThreadedOperation/ThreadedOperation.h \
   ./GlobalShortcut/GlobalShortcutManager.h \
   ./GlobalShortcut/GlobalShortcut.h
SOURCES +=  ./FileUtils.cpp \
   ./Exception.cpp \
   ./RandomNumberGenerator.cpp \
   ./stdafx.cpp \
   ./StringUtils.cpp \
   ./SystemUtils.cpp \
   ./StyleSheetEditor/StyleSheetEditor.cpp \
   ./DebugLog/DebugLog.cpp \
   ./DebugLog/DebugLogEntry.cpp \
   ./DebugLog/DebugLogFilterProxyModel.cpp \
   ./DebugLog/DebugLogWindow.cpp \
   ./ThreadedOperation/ThreadedOperation.cpp \
   ./ThreadedOperation/ThreadedOperationDialog.cpp \
   ./GlobalShortcut/GlobalShortcut.cpp \
   ./GlobalShortcut/GlobalShortcutManager.cpp
FORMS += ./StyleSheetEditor/StyleSheetEditor.ui \
   ./DebugLog/DebugLogWindow.ui \
   ./ThreadedOperation/ThreadedOperationDialog.ui
TRANSLATIONS += ./Translations/xmilib_fr.ts
