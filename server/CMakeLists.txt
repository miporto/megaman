project(server)

set(SOURCES
    Acceptor.cpp
    Acceptor.h
    main.cpp
    Match.cpp
    Match.h
    Server.cpp
    Server.h
    Communicator.h 
    Communicator.cpp 
    QuitProtected.h 
    QuitProtected.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} common)
