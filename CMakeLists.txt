cmake_minimum_required (VERSION 2.8.4)
project (Megaman)

set (CMAKE_CXX_STANDARD 98)

if(CMAKE_COMPILER_IS_GNUCXX)
    # Errors and warnings.
    set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -Wconversion -Wtype-limits -pedantic -pedantic-errors")
    # Valgrind and debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -ggdb -DDEBUG")
    # Optimizing
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

find_package(PkgConfig REQUIRED)
find_package (Threads REQUIRED)

pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(SYSTEM ${CAIROMM_INCLUDE_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})
add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(server)
