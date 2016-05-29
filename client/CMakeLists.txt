project(client)

set(SOURCES
        communication/Client.cpp
        communication/Client.h
        main.cpp
        view/MainWindow.cpp
        view/MainWindow.h
        communication/ClientCommunicator.h
        communication/ClientCommunicator.cpp
        view/GladeLoader.cpp
        view/GladeLoader.h
        view/SignalProtocol.h
        view/StageSurface.cpp
        view/StageSurface.h
        view/MegamanRenderer.cpp
        view/MegamanRenderer.h
        view/InputHandler.cpp
        view/InputHandler.h
        view/StageRenderer.cpp
        view/StageRenderer.h)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2PP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} common)
