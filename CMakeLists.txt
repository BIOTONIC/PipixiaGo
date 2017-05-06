#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/
cmake_policy(SET CMP0017 NEW)

cmake_minimum_required(VERSION 3.1)

set(APP_NAME PipixiaGo)
project(${APP_NAME})

#/****************************************************************************
# Add By lovejoy
link_directories(lib)
include_directories(include)
# ****************************************************************************/

set(COCOS2D_ROOT ${CMAKE_SOURCE_DIR}/cocos2d)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${COCOS2D_ROOT}/cmake/Modules/")
include(CocosBuildHelpers)

# libcocos2d
set(BUILD_CPP_EMPTY_TEST OFF CACHE BOOL "turn off build cpp-empty-test")
set(BUILD_CPP_TESTS OFF CACHE BOOL "turn off build cpp-tests")
set(BUILD_LUA_LIBS OFF CACHE BOOL "turn off build lua related targets")
set(BUILD_JS_LIBS OFF CACHE BOOL "turn off build js related targets")
add_subdirectory(${COCOS2D_ROOT})

# Some macro definitions
if (WINDOWS)
    if (BUILD_SHARED_LIBS)
        ADD_DEFINITIONS(-D_USRDLL -D_EXPORT_DLL_ -D_USEGUIDLL -D_USREXDLL -D_USRSTUDIODLL)
    else ()
        ADD_DEFINITIONS(-DCC_STATIC)
    endif ()

    ADD_DEFINITIONS(-DCOCOS2DXWIN32_EXPORTS -D_WINDOWS -DWIN32 -D_WIN32)
    set(PLATFORM_FOLDER win32)
elseif (MACOSX)
    ADD_DEFINITIONS(-DCC_TARGET_OS_MAC)
    ADD_DEFINITIONS(-DUSE_FILE32API)
    set(PLATFORM_FOLDER mac)
else ()
    message(FATAL_ERROR "Unsupported platform, CMake will exit")
endif ()


# Compiler options
if (MSVC)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt /NODEFAULTLIB:libcmt")
    else ()
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:libcmt")
    endif ()
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS
            -wd4251 -wd4244 -wd4334 -wd4005 -wd4820 -wd4710
            -wd4514 -wd4056 -wd4996 -wd4099)
else ()
    set(CMAKE_C_FLAGS_DEBUG "-g -Wall -DCOCOS2D_DEBUG=1")
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-deprecated-declarations -Wno-reorder")
    if (CLANG)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif (MSVC)


set(PLATFORM_SPECIFIC_SRC)
set(PLATFORM_SPECIFIC_HEADERS)

if (MACOSX)
    set(PLATFORM_SPECIFIC_SRC
            proj.mac/main.cpp
            )
elseif (WIN32)
    set(PLATFORM_SPECIFIC_SRC
            proj.win32/main.cpp
            )
    set(PLATFORM_SPECIFIC_HEADERS
            proj.win32/main.h
            proj.win32/resource.h
            )
endif ()

include_directories(
        /usr/local/include/GLFW
        /usr/include/GLFW
        ${COCOS2D_ROOT}/cocos
        ${COCOS2D_ROOT}/cocos/platform
        ${COCOS2D_ROOT}/cocos/audio/include/
        Classes
)
if (WIN32)
    include_directories(
            ${COCOS2D_ROOT}/external/glfw3/include/win32
            ${COCOS2D_ROOT}/external/win32-specific/gles/include/OGLES
    )
endif (WIN32)

set(GAME_SRC
        Classes/AppDelegate.cpp
        Classes/Cube.cpp
        Classes/Entity.cpp
        CLasses/StartScene.cpp
        Classes/GameScene.cpp
        Classes/SceneManager.cpp
        Classes/ResultScene.cpp
        ${PLATFORM_SPECIFIC_SRC}
        )

set(GAME_HEADERS
        Classes/AppDelegate.h
        Classes/Cube.h
        Classes/Entity.h
        Classes/StartScene.h
        Classes/GameScene.h
        Classes/SceneManager.h
        Classes/ResultScene.h
        Classes/PortInclude.h
        ${PLATFORM_SPECIFIC_HEADERS}
        )

add_executable(${APP_NAME} ${GAME_SRC} ${GAME_HEADERS})


#/****************************************************************************
# Add By lovejoy

find_library(carbon_lib Carbon)
find_library(audiounit_lib Audiounit)
find_library(coreaudio_lib Coreaudio)
find_library(audioToolbox_lib AudioToolbox)
find_library(coreServices_lib CoreServices)

if (NOT carbon_lib)
    message(FATAL_ERROR "carbon_lib not found")
endif ()
if (NOT audiounit_lib)
    message(FATAL_ERROR "AudioUnit not found")
endif ()
if (NOT coreaudio_lib)
    message(FATAL_ERROR "coreaudio_lib not found")
endif ()
if (NOT audioToolbox_lib)
    message(FATAL_ERROR "audioToolbox_lib not found")
endif ()
if (NOT coreServices_lib)
    message(FATAL_ERROR "coreServices_lib not found")
endif ()

set(frameworks
        ${carbon_lib}
        ${audiounit_lib}
        ${coreaudio_lib}
        ${audioToolbox_lib}
        ${coreServices_lib})

# target_link_libraries(${APP_NAME} cocos2d)
target_link_libraries(${APP_NAME} cocos2d libportaudio.a ${frameworks})

# End
# ****************************************************************************/

set(APP_BIN_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${APP_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${APP_BIN_DIR}")

if (WIN32)
    #also copying dlls to binary directory for the executable to run
    pre_build(${APP_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/gles/prebuilt/glew32.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
            COMMAND ${CMAKE_COMMAND} -E copy ${COCOS2D_ROOT}/external/win32-specific/zlib/prebuilt/zlib1.dll ${APP_BIN_DIR}/${CMAKE_BUILD_TYPE}
            )
else ()
    pre_build(${APP_NAME}
            COMMAND ${CMAKE_COMMAND} -E remove_directory ${APP_BIN_DIR}/Resources
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Resources ${APP_BIN_DIR}/Resources
            )

endif ()
