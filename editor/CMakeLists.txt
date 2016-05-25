project(editor)

set(SOURCES
    main.cpp
    EditorWindow.cpp
    EditorWindow.h)

include(CppLint)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
