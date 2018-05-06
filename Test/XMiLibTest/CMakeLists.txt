cmake_minimum_required(VERSION 3.10)
project(XMiLibTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("../..")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)


find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Test)

add_executable(XMiLibTest
   DebugLogTest.cpp
   ExceptionTest.cpp
   FileUtilsTest.cpp
   GlobalShortcutTest.cpp
   RandomNumberGeneratorTest.cpp
   stdafx.cpp
   stdafx.h
   StringUtilsTest.cpp
   ThreadedOperationTest.cpp
   XMiLibTest.cpp
   XMiLibTest.h)

target_link_libraries(XMiLibTest Qt5::Core)
target_link_libraries(XMiLibTest Qt5::Test)
target_link_libraries(XMiLibTest Qt5::Gui)
target_link_libraries(XMiLibTest XMiLib)
