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

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package (PkgConfig REQUIRED)
find_package (Threads REQUIRED)
include(CppLint)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(server)
