project(server)

set(SOURCES
        communication/Acceptor.cpp
        communication/Acceptor.h
    main.cpp
        communication/Match.cpp
        communication/Match.h
        communication/Server.cpp
        communication/Server.h
        communication/ServerCommunicator.h
        communication/ServerCommunicator.cpp
        model/Stage.h
        model/Stage.cpp
        model/Factory.cpp
        model/Factory.h
        model/Position.h
        model/Position.cpp
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
        model/Game.h model/Movable.cpp model/Movable.h communication/TickInfoMaker.cpp communication/TickInfoMaker.h communication/EventQueue.cpp communication/EventQueue.h model/GameObject.cpp model/GameObject.h model/ServerStageSetter.cpp model/ServerStageSetter.h model/Player.cpp model/Player.h model/BossChamber.cpp model/BossChamber.h Logger.cpp Logger.h)

include(CppLint)

SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES COMPILE_FLAGS "-Wno-conversion")

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)
add_dependencies(${PROJECT_NAME} extern)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${LOG4CPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} common)
target_link_libraries(${PROJECT_NAME} extern)