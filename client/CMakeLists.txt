CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(client)
SET(CLIENT_SOURCES 

clientpch.cpp
client.cpp
canvas.cpp
clienteventfactory.cpp
clienteventdispatcher.cpp
clienteventhandler.cpp
renderer.cpp
)

set(CLIENT_HEADERS

clientpch.h
client.h
canvas.h
clienteventfactory.h
clienteventdispatcher.h
clienteventhandler.h
renderer.h
)


SET(CMAKE_OSX_ARCHITECTURES i386)


INCLUDE_DIRECTORIES(../common)
INCLUDE_DIRECTORIES(/usr/include/freetype2)

ADD_EXECUTABLE(client ${CLIENT_SOURCES})

FIND_PACKAGE(FLTK REQUIRED)
INCLUDE_DIRECTORIES(${FLTK_INCLUDE_DIR})

find_package(OpenGL REQUIRED)

TARGET_LINK_LIBRARIES(client ${FLTK_LIBRARIES} common ${OPENGL_LIBRARIES})
