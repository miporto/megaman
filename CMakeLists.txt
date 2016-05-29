cmake_minimum_required (VERSION 2.8.4)
project (MegaMan)

if(CMAKE_COMPILER_IS_GNUCXX)
    # Errors and warnings.
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wconversion -Wno-unused-parameter -Wextra -Wtype-limits -pedantic -pedantic-errors")
    # Gtkmm
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-inline -DG_DISABLE_DEPRECATED -DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED -DGDKMM_DISABLE_DEPRECATED -DGTKMM_DISABLE_DEPRECATED")
    # Valgrind and debug
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} -O0 -ggdb3 -DDEBUG")
    # Optimizing
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG")
endif(CMAKE_COMPILER_IS_GNUCXX)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
find_package (PkgConfig REQUIRED)
find_package (Threads REQUIRED)
find_package(Box2D REQUIRED)
include(CppLint)

pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
pkg_check_modules(SDL2 REQUIRED sdl2)
# Configure SDL2 wrapper
SET(SDL2PP_WITH_IMAGE ON)
SET(SDL2PP_WITH_TTF ON)
add_subdirectory(extern/libSDL2pp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(SYSTEM ${CAIROMM_INCLUDE_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})
include_directories(SYSTEM ${SDL2_INCLUDE_DIRS})
include_directories(SYSTEM ${SDL2PP_INCLUDE_DIRS})
include_directories(SYSTEM ${BOX2D_INCLUDE_DIR})
add_subdirectory(client)
add_subdirectory(common)
add_subdirectory(editor)
add_subdirectory(examples)
add_subdirectory(extern)
add_subdirectory(server)
