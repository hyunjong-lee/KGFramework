CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(KGServer)

SET(KGSERVER_SOURCES 

KGServerPCH.cpp
KGServer.cpp
ServerEventFactory.cpp
ServerEventDispatcher.cpp
ServerEventHandler.cpp
)

set(KGSERVER_HEADERS

KGServerPCH.h
ServerEventFactory.h
ServerEventDispatcher.h
ServerEventHandler.h
)


SET(CMAKE_OSX_ARCHITECTURES i386)

INCLUDE_DIRECTORIES(../KGCommon)

ADD_EXECUTABLE(KGServer ${KGSERVER_SOURCES})

ADD_DEPENDENCIES(KGServer KGCommon)
