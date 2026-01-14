cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)

project(fsf VERSION 0.5.0 LANGUAGES C CXX)

set(PROJECT_IS_TOP_LEVEL TRUE)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(FSF_BUILD_TESTS "Build tests" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32 AND BUILD_SHARED_LIBS)
    add_definitions(-DMI_FSF_EXPORTS)
endif()

add_library(fsf)
add_library(fsf::fsf ALIAS fsf)

target_sources(fsf
    PRIVATE src/fsf.cpp
    PUBLIC include/fsf/fsf.h
)

set_target_properties(fsf PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "include/fsf/fsf.h"
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)

target_include_directories(fsf
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/fsf>
        $<INSTALL_INTERFACE:include/fsf>
)


