project(client)

set(SOURCES
    main.cpp
    clientMegamanClient.h
    clientMegamanClient.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} common)
