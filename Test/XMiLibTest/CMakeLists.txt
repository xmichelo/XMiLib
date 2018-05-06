cmake_minimum_required(VERSION 3.10)
project(XMiLibTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


include_directories("../..")


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)


if (NOT DEFINED WIN32)
   if (DEFINED ENV{QTDIR})
      set(CMAKE_PREFIX_PATH  ${CMAKE_PREFIX_PATH} $ENV{QTDIR})
   else()
      message(FATAL_ERROR "QTDIR needs to be defined and point to the root of your Qt folder. "
         "(e.g. /Users/MyName/Qt/5.10.1/clang_64).")
   endif()
endif()


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
