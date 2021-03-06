project(base)

cmake_minimum_required(VERSION 2.8.5)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif ()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG_BUILD")

if (${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions("-std=c++0x")
else (${CMAKE_COMPILER_IS_GNUCXX})
    add_definitions("-std=c++11")
endif (${CMAKE_COMPILER_IS_GNUCXX})

add_definitions("-Wall")
add_definitions("-pedantic")
add_definitions("-Wextra")
add_definitions("-fvisibility=hidden")

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

find_package(PkgConfig)

set(TARGET_BASE "base")

include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(src)
add_subdirectory(tests)
