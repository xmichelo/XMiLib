cmake_minimum_required(VERSION 3.23)

project(XMiLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_program(QMAKE_EXE "qmake")
if (NOT QMAKE_EXE)
    message(FATAL_ERROR "Could not locate qmake executable, make sur you have Qt 6 installed in that qmake is in your PATH environment variable.")
 endif()
message(STATUS "Found qmake at ${QMAKE_EXE}")

execute_process(COMMAND "${QMAKE_EXE}" -query QT_INSTALL_PREFIX OUTPUT_VARIABLE QT_DIR OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "Qt dir is ${QT_DIR}")

set(CMAKE_PREFIX_PATH QT_DIR ${CMAKE_PREFIX_PATH})

find_package(Qt6Core)
find_package(Qt6Gui)
find_package(Qt6Widgets)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)

add_definitions(-DUNICODE -D_UNICODE)

if (DEFINED WIN32)
   set(WINDOWS_ONLY_SOURCE_FILES
      GlobalShortcut/GlobalShortcut.cpp
      GlobalShortcut/GlobalShortcut.h
      GlobalShortcut/GlobalShortcutManager.cpp
      GlobalShortcut/GlobalShortcutManager.h
      Scoped/ScopedClipboardAccess.cpp
      Scoped/ScopedClipboardAccess.h
      Scoped/ScopedGlobalMemoryLock.cpp
      Scoped/ScopedGlobalMemoryLock.h)
else()
   set(WINDOWS_ONLY_SOURCE_FILES)
endif()

add_library(XMiLib STATIC
   DebugLog/DebugLog.cpp
   DebugLog/DebugLog.h
   DebugLog/DebugLogEntry.cpp
   DebugLog/DebugLogEntry.h
   DebugLog/DebugLogFilterProxyModel.cpp
   DebugLog/DebugLogFilterProxyModel.h
   DebugLog/DebugLogWindow.cpp
   DebugLog/DebugLogWindow.h
   DebugLog/DebugLogWindow.ui
   File/FileUtils.cpp
   File/FileUtils.h
   File/CsvIO.cpp
   File/CsvIO.h
   String/StringListEditorDialog.cpp
   String/StringListEditorDialog.h
   String/StringListEditorDialog.ui
   String/StringListEditorModel.cpp
   String/StringListEditorModel.h
   String/StringUtils.cpp
   String/StringUtils.h
   StyleSheetEditor/StyleSheetEditor.cpp
   StyleSheetEditor/StyleSheetEditor.h
   StyleSheetEditor/StyleSheetEditor.ui
   ThreadedOperation/ThreadedOperation.cpp
   ThreadedOperation/ThreadedOperation.h
   ThreadedOperation/ThreadedOperationDialog.cpp
   ThreadedOperation/ThreadedOperationDialog.h
   ThreadedOperation/ThreadedOperationDialog.ui
   VersionNumber/VersionNumber.cpp
   VersionNumber/VersionNumber.h
   Exception.cpp
   Exception.h
   RandomNumberGenerator.cpp
   RandomNumberGenerator.h
   SingleInstanceApp.cpp
   SingleInstanceApp.h
   stdafx.cpp
   stdafx.h
   SystemUtils.cpp
   SystemUtils.h
   ${WINDOWS_ONLY_SOURCE_FILES})

#target_precompile_headers(XMiLib PUBLIC stdafx.h) Buggy the moment, so it is disabled.
target_link_libraries(XMiLib Qt6::Core)
target_link_libraries(XMiLib Qt6::Gui)
target_link_libraries(XMiLib Qt6::Widgets)
if (DEFINED WIN32)
target_link_libraries(XMiLib Psapi)
target_link_libraries(XMiLib Kernel32)
endif()