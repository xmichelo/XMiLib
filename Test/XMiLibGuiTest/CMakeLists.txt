cmake_minimum_required(VERSION 3.10)

project(XMiLibGuiTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (NOT DEFINED ENV{QTDIR})
   message(FATAL_ERROR "QTDIR needs to be defined and point to the root of your Qt folder. "
      "(e.g. /Users/MyName/Qt/5.10.1/clang_64).")
endif()

set(CMAKE_PREFIX_PATH  $ENV{QTDIR} ${CMAKE_PREFIX_PATH})

find_package(Qt6Core)
find_package(Qt6Gui)
find_package(Qt6Widgets)

include_directories("../..")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)

add_executable(XMiLibGuiTest
   Constants.cpp
   Constants.h
   main.cpp
   MainWindow.cpp
   MainWindow.h
   MainWindow.ui
   OriginalStyleSheet.cpp
   OriginalStyleSheet.h
   stdafx.cpp
   stdafx.h)

target_precompile_headers(XMiLibGuiTest PUBLIC stdafx.h)
target_link_libraries(XMiLibGuiTest Qt6::Core)
target_link_libraries(XMiLibGuiTest Qt6::Gui)
target_link_libraries(XMiLibGuiTest Qt6::Widgets)
target_link_libraries(XMiLibGuiTest XMiLib)
