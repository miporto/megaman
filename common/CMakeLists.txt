project(common)

set(SOURCES
    AddrInfo.cpp
    AddrInfo.h
    Socket.cpp
    Socket.h
    Thread.cpp
    Thread.h
    Sender.h
    Sender.cpp
    Receiver.h
    Receiver.cpp
    QuitProtected.h
    QuitProtected.cpp
    Packet.h
    Packet.cpp ScreenInfo.h ScreenInfo.cpp)

include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
