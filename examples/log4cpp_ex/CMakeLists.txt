project(log4cpp_ex)

SET(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${LOG4CPP_LIBRARIES})