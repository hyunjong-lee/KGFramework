CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(ARAN_LIBRARIES
  aranmath
  aran
  arangl
)
MACRO(ADD_MSVC_PRECOMPILED_HEADER tgt hdr src)
if (MSVC)
  set_target_properties(${tgt} PROPERTIES COMPILE_FLAGS "/Yu\"${hdr}\"")
  set_source_files_properties(${src} PROPERTIES COMPILE_FLAGS "/Yc\"${hdr}\"")
endif(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)

PROJECT(client)
SET(CLIENT_SOURCES 

clientpch.cpp
client.cpp
canvas.cpp
clienteventfactory.cpp
clienteventdispatcher.cpp
clienteventhandler.cpp
renderer.cpp
car.cpp
)

set(CLIENT_HEADERS

clientpch.h
client.h
canvas.h
clienteventfactory.h
clienteventdispatcher.h
clienteventhandler.h
renderer.h
car.cpp
)


SET(CMAKE_OSX_ARCHITECTURES i386)

INCLUDE_DIRECTORIES(/usr/include/freetype2)
INCLUDE_DIRECTORIES(../common)
INCLUDE_DIRECTORIES(../aran/include)
INCLUDE_DIRECTORIES(../aran/include/aran)
INCLUDE_DIRECTORIES(../aran/include/aranmath)
INCLUDE_DIRECTORIES(../aran/include/aran)
INCLUDE_DIRECTORIES(../aran/include/arangl)

if (MSVC10)
  LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../aran/lib/vc10)
endif (MSVC10)
if (MSVC90)
  LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../aran/lib/vc90)
endif (MSVC90)
if (MSVC80)
  LINK_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../aran/lib/vc80)
endif (MSVC80)

ADD_EXECUTABLE(client ${CLIENT_SOURCES})

FIND_PACKAGE(FLTK REQUIRED)
INCLUDE_DIRECTORIES(${FLTK_INCLUDE_DIR})

find_package(OpenGL REQUIRED)

TARGET_LINK_LIBRARIES(client
  ${FLTK_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${ARAN_LIBRARIES}
  common
)
ADD_MSVC_PRECOMPILED_HEADER(client clientpch.h clientpch.cpp)

#if (MSVC)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/aran/vs2010/aranmath.dll
#    ${CMAKE_BINARY_DIR}/aranmath.dll COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/aran/vs2010/aran.dll
#    ${CMAKE_BINARY_DIR}/aran.dll COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/aran/vs2010/arangl.dll
#    ${CMAKE_BINARY_DIR}/arangl.dll COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/aran/vs2010/aranik.dll
#    ${CMAKE_BINARY_DIR}/aranik.dll COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/devil/devil.dll
#    ${CMAKE_BINARY_DIR}/devil.dll COPYONLY)
#configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../lib/zlib/zlib1.dll
#    ${CMAKE_BINARY_DIR}/zlib1.dll COPYONLY)
#endif (MSVC)
