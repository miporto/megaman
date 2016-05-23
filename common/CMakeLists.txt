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
    Packet.cpp
    StageInfo.h
    StageInfo.cpp
        model/Position.h
        model/Position.cpp
        model/Player.h
        model/Player.cpp
        model/Object.h
        model/Object.cpp
        model/Enemy.h
        model/Enemy.cpp
        model/MegaMan.h
        model/MegaMan.cpp
        model/Cannon.h
        model/Cannon.cpp
        model/Map.h
        model/Map.cpp model/Game.cpp model/Game.h)

include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
