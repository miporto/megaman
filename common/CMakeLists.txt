project(common)

set(SOURCES
        communication/AddrInfo.cpp
        communication/AddrInfo.h
        communication/Socket.cpp
        communication/Socket.h
    Thread.cpp
    Thread.h
        communication/Sender.h
        communication/Sender.cpp
        communication/Receiver.h
        communication/Receiver.cpp
        communication/QuitProtected.h
        communication/QuitProtected.cpp
        communication/Packet.h
        communication/Packet.cpp
        communication/StageInfo.h
        communication/StageInfo.cpp
    Position.h
    Position.cpp)

include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
