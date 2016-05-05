project(server)

set(SOURCES
    serverAcceptor.cpp
    serverAcceptor.h
    server.cpp
    serverMatch.cpp
    serverMatch.h
    serverMegamanServer.cpp
    serverMegamanServer.h
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} common)
