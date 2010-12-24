CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(server)

SET(SERVER_SOURCES 

serverpch.cpp
server.cpp
serverprocess.cpp
servercore.cpp
servereventfactory.cpp
servereventdispatcher.cpp
servereventhandler.cpp
)

set(SERVER_HEADERS

serverpch.h
serverprocess.h
servercore.hpp
clienthandler.hpp
serverinterface.hpp
servereventfactory.h
servereventdispatcher.h
servereventhandler.h
)


SET(CMAKE_OSX_ARCHITECTURES i386)

INCLUDE_DIRECTORIES(../common)

ADD_EXECUTABLE(server ${SERVER_SOURCES})

ADD_DEPENDENCIES(server common)

TARGET_LINK_LIBRARIES(server common)
