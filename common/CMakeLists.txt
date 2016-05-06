project(common)

set(SOURCES
    AddrInfo.cpp
    AddrInfo.h
    Socket.cpp
    Socket.h
    Thread.cpp
    Thread.h
)

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
