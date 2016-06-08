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
    Position.h
    Position.cpp SystemError.cpp SystemError.hs StageParser.cpp StageParser.h)

include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES COMPILE_FLAGS "-Wno-conversion")
add_dependencies(${PROJECT_NAME} extern)

target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

target_link_libraries(${PROJECT_NAME} extern)