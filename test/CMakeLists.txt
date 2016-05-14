project(unitTests)

set(SOURCES
    bool_test.cpp
    number_test.cpp
    main.cpp)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
#include_directories(${GTEST_INCLUDE_DIRS})

#target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
add_test(${PROJECT_NAME} ${PROJECT_NAME})

