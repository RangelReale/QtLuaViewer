cmake_minimum_required(VERSION 2.8)

project(qtluaviewer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package (Threads)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)


find_package(Qt5Widgets REQUIRED)


FIND_PACKAGE(Lua REQUIRED)
#IF(LUA_FOUND)
  INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
#  LINK_DIRECTORIES(${LUA_LIBRARIES})
#ENDIF(LUA_FOUND)

FIND_PACKAGE(LuaIntf REQUIRED)
INCLUDE_DIRECTORIES(${LUAINTF_INCLUDE_DIRS})

SET( TARGET_BASE_NAME qtluaviewer )

#-----------------------------------------------------------------------------

SET( EXE_NAME "${TARGET_BASE_NAME}" )

# Add any source files here.
SET( EXE_SRCS
	LuaStateWidget.cpp
)

# Add any include files here.
SET( EXE_INCS
	LuaStateWidget.h
)

#-----------------------------------------------------------------------------

SET(BASE_SRCS
		main.cpp
)
SET(BASE_INCS
)

# The executable.
ADD_EXECUTABLE(${EXE_NAME} ${BASE_SRCS} ${BASE_INCS} ${EXE_SRCS} ${EXE_INCS})

TARGET_LINK_LIBRARIES ( ${EXE_NAME}
  ${LUA_LIBRARIES}
  
  ${CMAKE_THREAD_LIBS_INIT}
  ${CMAKE_DL_LIBS}
)

qt5_use_modules(${EXE_NAME} Widgets)

