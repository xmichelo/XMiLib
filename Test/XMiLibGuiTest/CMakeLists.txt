cmake_minimum_required(VERSION 3.10)
project(XMiLibGuiTest)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)

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

target_link_libraries(XMiLibGuiTest Qt5::Core)
target_link_libraries(XMiLibGuiTest Qt5::Gui)
target_link_libraries(XMiLibGuiTest Qt5::Widgets)
target_link_libraries(XMiLibGuiTest XMiLib)
