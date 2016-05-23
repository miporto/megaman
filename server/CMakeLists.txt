project(server)

set(SOURCES
    Acceptor.cpp
    Acceptor.h
    main.cpp
    Match.cpp
    Match.h
    Server.cpp
    Server.h
    ServerCommunicator.h
    ServerCommunicator.cpp
    Stage.h 
    Stage.cpp
        model/Factory.cpp
        model/Factory.h
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
        model/Map.cpp
        model/Game.cpp
        model/Game.h)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} common)
