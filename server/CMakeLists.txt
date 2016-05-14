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
    Player.h 
    Player.cpp
    Object.h
    Object.cpp
    Enemy.h
    Enemy.cpp)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} common)