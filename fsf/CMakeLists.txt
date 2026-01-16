cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(fsf VERSION 0.5.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libs" ON)
option(FSF_BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FSF_SOURCES src/fsf.cpp)

add_library(fsf ${FSF_SOURCES})
add_library(fsf::fsf ALIAS fsf)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(fsf PRIVATE FSF_BUILD_DLL)
    
    if(MINGW OR UNIX)
        set_target_properties(fsf PROPERTIES
            CXX_VISIBILITY_PRESET hidden
            VISIBILITY_INLINES_HIDDEN ON
        )
    endif()
endif()

set_target_properties(fsf PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME "fsf"
    DEBUG_POSTFIX "d"
    PUBLIC_HEADER "include/fsf/fsf.h"
)

target_include_directories(fsf
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

include(GNUInstallDirs)

install(TARGETS fsf
    EXPORT fsfTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fsf
)

install(FILES include/fsf/fsf.h DESTINATION include/fsf)

install(EXPORT fsfTargets
    FILE fsfConfig.cmake
    NAMESPACE fsf::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsf
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/fsfConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/fsfConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fsf
)

if(FSF_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
