project(client)

set(SOURCES
        view/AboutScreen.cpp
        view/AboutScreen.h
        communication/Client.cpp
        communication/Client.h
        main.cpp
        view/MainWindow.cpp
        view/MainWindow.h
        communication/ClientCommunicator.h
        communication/ClientCommunicator.cpp
        view/GladeLoader.cpp
        view/GladeLoader.h
        view/SignalProtocol.h TickInfoParser.cpp TickInfoParser.h)

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
