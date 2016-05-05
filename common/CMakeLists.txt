project(common)

set(SOURCES
    commonAddrInfo.cpp
    commonAddrInfo.h
    commonSocket.cpp
    commonSocket.h
    commonThread.cpp
    commonThread.h
)

add_library(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
