CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(common)

SET(COMMON_SOURCES 

commonpch.cpp
abstractevent.cpp
character.cpp
commonapi.cpp
)

set(COMMON_HEADERS

commonpch.h
character.h
macro.h
commonapi.h
)


SET(CMAKE_OSX_ARCHITECTURES i386)


ADD_DEFINITIONS(-D_USRDLL -DKGCOMMON_EXPORTS)
ADD_LIBRARY(common SHARED ${COMMON_SOURCES})
