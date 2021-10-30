cmake_minimum_required(VERSION 3.10)

project(XMiLibTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("../..")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC_MOC_OPTIONS "-bstdafx.h")
set(CMAKE_AUTOMOC ON)

if (NOT DEFINED ENV{QTDIR})
   message(FATAL_ERROR "QTDIR needs to be defined and point to the root of your Qt folder. "
      "(e.g. /Users/MyName/Qt/5.10.1/clang_64).")
endif()

set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})

find_package(Qt6Core)
find_package(Qt6Gui)
find_package(Qt6Test)

if (DEFINED WIN32)
   set(WINDOWS_ONLY_SOURCE_FILES
      GlobalShortcutTest.cpp
      ScopedClipboardAccess.cpp
      ScopedGlobalMemoryLockTest.cpp)
else()
   set(WINDOWS_ONLY_SOURCE_FILES)
endif()

add_executable(XMiLibTest
   CsvTest.cpp
   DebugLogTest.cpp
   ExceptionTest.cpp
   FileUtilsTest.cpp
   RandomNumberGeneratorTest.cpp
   stdafx.cpp
   stdafx.h
   StringUtilsTest.cpp
   ThreadedOperationTest.cpp
   XMiLibTest.cpp
   XMiLibTest.h
   ${WINDOWS_ONLY_SOURCE_FILES})

target_precompile_headers(XMiLibTest PUBLIC stdafx.h)
target_link_libraries(XMiLibTest Qt6::Core)
target_link_libraries(XMiLibTest Qt6::Test)
target_link_libraries(XMiLibTest Qt6::Gui)
target_link_libraries(XMiLibTest XMiLib)
