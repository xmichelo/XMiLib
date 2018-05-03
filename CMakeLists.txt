cmake_minimum_required(VERSION 3.10)
project(XMiLib)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

find_package(Qt5Core)
find_package(Qt5Widgets)

set(CMAKE_AUTOMOC_ON)
set(CMAKE_AUTOUIC ON)

add_definitions(-DUNICODE -D_UNICODE)

add_library(XMiLib
        DebugLog/DebugLog.cpp
        DebugLog/DebugLog.h
        DebugLog/DebugLogEntry.cpp
        DebugLog/DebugLogEntry.h
        DebugLog/DebugLogFilterProxyModel.cpp
        DebugLog/DebugLogFilterProxyModel.h
        DebugLog/DebugLogWindow.cpp
        DebugLog/DebugLogWindow.h
        DebugLog/DebugLogWindow.ui
        GlobalShortcut/GlobalShortcut.cpp
        GlobalShortcut/GlobalShortcut.h
        GlobalShortcut/GlobalShortcutManager.cpp
        GlobalShortcut/GlobalShortcutManager.h
        StyleSheetEditor/StyleSheetEditor.cpp
        StyleSheetEditor/StyleSheetEditor.h
        StyleSheetEditor/StyleSheetEditor.ui
        ThreadedOperation/ThreadedOperation.cpp
        ThreadedOperation/ThreadedOperation.h
        ThreadedOperation/ThreadedOperationDialog.cpp
        ThreadedOperation/ThreadedOperationDialog.h
        ThreadedOperation/ThreadedOperationDialog.ui
        Exception.cpp
        Exception.h
        FileUtils.cpp
        FileUtils.h
        RandomNumberGenerator.cpp
        RandomNumberGenerator.h
        stdafx.cpp
        stdafx.h
        StringUtils.cpp
        StringUtils.h
        SystemUtils.cpp
        SystemUtils.h)

target_link_libraries(XMiLib Qt5::Widgets)