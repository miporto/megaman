project(client)

set(SOURCES
    main.cpp
    Client.h
    Client.cpp
)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} common)
