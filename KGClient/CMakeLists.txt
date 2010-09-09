CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(KGClient)

SET(KGCLIENT_SOURCES 

KGClientPCH.cpp
KGClient.cpp
ClientEventFactory.cpp
ClientEventDispatcher.cpp
ClientEventHandler.cpp
)

set(KGCLIENT_HEADERS

KGClientPCH.h
KGClient.h
ClientEventFactory.h
ClientEventDispatcher.h
ClientEventHandler.h
)

INCLUDE_DIRECTORIES(../KGCommon)
INCLUDE_DIRECTORIES(/usr/include/freetype2)

ADD_EXECUTABLE(KGClient ${KGCLIENT_SOURCES})

FIND_PACKAGE(FLTK REQUIRED)
INCLUDE_DIRECTORIES(${FLTK_INCLUDE_DIR})


TARGET_LINK_LIBRARIES(KGClient ${FLTK_LIBRARIES} KGCommon)
