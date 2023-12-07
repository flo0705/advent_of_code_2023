cmake_minimum_required(VERSION 3.20)
if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ext/better-cmake/cmake/betterConfig.cmake")
    execute_process(COMMAND git submodule update --init "${CMAKE_CURRENT_SOURCE_DIR}/ext/better-cmake" WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}") 
endif()
find_package(better REQUIRED NO_DEFAULT_PATH PATHS ext/better-cmake/cmake)

project(aoc23)
project_author("flo0705")

add_exe(aoc
    VERSION 0.0.1
    SOURCES_DIR "${ROOT}/src"
    CPP_VERSION 17
    CPP_WARNINGS ALL SANE FATAL
    EXT
        LIB shl 0.8.2 "${ROOT}/ext/shl" INCLUDE LINK
    )


