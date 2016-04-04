cmake_minimum_required(VERSION 2.8.9)
project("cMark")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS " -lsqlite3 ")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    set(CMAKE_EXE_LINKER_FLAGS " -lsqlite3 ")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_path(SQLITE3_INCLUDE_DIR sqlite3.h)
find_library(SQLITE3_LIBRARY sqlite3)

if(NOT SQLITE3_INCLUDE_DIR)
  message(SEND_ERROR "Failed to find sqlite3.h")
endif()
if(NOT SQLITE3_LIBRARY)
  message(SEND_ERROR "Failed to find the sqlite3 library")
endif()

include_directories(include/db)
include_directories(include/)
                      

if(UNIX)
  if(APPLE)
    include_directories(include/platforms/osx_deviceinfo.h)
    file(GLOB SOURCES "src/*.cpp" 
                      "src/db/*.cpp"
                      "src/platforms/osx*.cpp")
  else(APPLE)
    include_directories(include/platforms/linux_deviceinfo.h)
    file(GLOB SOURCES "src/*.cpp" 
                      "src/db/*.cpp"
                      "src/platforms/linux*.cpp")
  endif(APPLE)
else(UNIX)
  if(WIN32)
     include_directories(include/platforms/win_deviceinfo.h)
     file(GLOB SOURCES "src/*.cpp" 
                       "src/db/*.cpp"
                       "src/platforms/win*.cpp")
  endif(WIN32)
endif(UNIX)

add_executable(build/cMark ${SOURCES})