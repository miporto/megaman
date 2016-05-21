project(client)

set(SOURCES
    AboutScreen.cpp
    AboutScreen.h
    Client.cpp
    Client.h
    main.cpp
    MainWindow.cpp
    MainWindow.h
    ClientCommunicator.h
    ClientCommunicator.cpp 
    GladeLoader.cpp 
    GladeLoader.h
    SignalProtocol.h)

include(CppLint)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} common)
