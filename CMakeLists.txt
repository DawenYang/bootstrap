cmake_minimum_required(VERSION 3.24)
project(bootstrap)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-private-field -Wno-unknown-pragmas -Wno-inconsistent-missing-override" CACHE STRING "compile flags" FORCE)
    message(STATUS "Using clang flags: ${CMAKE_CXX_FLAGS}")
elseif ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-Wall" CACHE STRING "compile flags" FORCE)
    message(STATUS "Using gcc flags: ${CMAKE_CXX_FLAGS}")
else ()
    message(STATUS "Unknown compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

# rpath setup
SET(CMAKE_SKIP_BUILD_RPATH FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "/usr/local/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# project cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake-build-debug")

include_directories(
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}
        ${FMT_INCLUDE_DIRS}
)

add_executable(bootstrap
        main.cpp terp.cpp terp.h result.h result_message.h hex_formatter.cpp hex_formatter.h)

find_package(fmt)

target_link_libraries(bootstrap fmt::fmt)
