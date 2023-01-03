cmake_minimum_required(VERSION 3.24)
project(bootstrap)


if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(bootstrap
        main.cpp terp.cpp terp.h result.h result_message.h)

find_package(fmt)

target_link_libraries(bootstrap fmt::fmt)
