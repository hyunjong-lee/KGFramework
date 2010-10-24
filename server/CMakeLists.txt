CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server)

SET(SERVER_SOURCES 

serverpch.cpp
server.cpp
servereventfactory.cpp
servereventdispatcher.cpp
servereventhandler.cpp
)

set(SERVER_HEADERS

serverpch.h
servereventfactory.h
servereventdispatcher.h
servereventhandler.h
)


SET(CMAKE_OSX_ARCHITECTURES i386)

INCLUDE_DIRECTORIES(../common)

ADD_EXECUTABLE(server ${SERVER_SOURCES})

ADD_DEPENDENCIES(server common)
