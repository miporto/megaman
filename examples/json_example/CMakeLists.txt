project(json_example)

set(SOURCES
    json_test.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})


add_dependencies(${PROJECT_NAME} extern)
SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES COMPILE_FLAGS "-Wno-conversion")

target_link_libraries(${PROJECT_NAME} extern)
