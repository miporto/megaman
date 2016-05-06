project(client)

set(SOURCES
    main.cpp
    Client.h
    Client.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} common)
