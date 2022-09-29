cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

project(image)

include(function.cmake)

add_subdirectory(main)
add_subdirectory(imagelib)

option(BTEST "build test?" OFF)


if(BTEST)
    add_subdirectory(gtest)
    add_subdirectory(test)
endif()
