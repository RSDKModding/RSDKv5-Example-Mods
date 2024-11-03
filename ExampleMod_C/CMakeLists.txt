# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(ExampleMod)

set(MOD_NAME ExampleMod CACHE STRING "The mod directory to look into")
set(OUTPUT_NAME "ExampleMod" CACHE STRING "The name of the built library")

set(RETRO_REVISION 3 CACHE STRING "What revision to compile for. Defaults to Origins = 3")
set(RETRO_MOD_LOADER_VER 2 CACHE STRING "Sets the mod loader version. Defaults to latest")

option(MANIA_FIRST_RELEASE "Whether or not to build Mania's first release. Defaults to false" OFF)
if(MANIA_FIRST_RELEASE)
    set(MANIA_PREPLUS ON)
else()
    option(MANIA_PREPLUS "Whether or not to build Mania pre-plus. Defaults to false" OFF)
endif()

if(NOT MANIA_PREPLUS)
    set(GAME_VERSION 6 CACHE STRING "The game version to use. Defaults to 6 == Last Steam release")
else()
    set(GAME_VERSION 3 CACHE STRING "The game version to use. Defaults to 3 == Last pre-plus release")
endif()

option(MOD_INCLUDE_EDITOR "Whether or not to include editor functions. Defaults to true" ON)

find_path(GAMEAPI
  NAMES
    C
    CPP
  PATHS
    .
    ..
  PATH_SUFFIXES
    GameAPI
    RSDKv5-GameAPI
  NO_DEFAULT_PATH
)

if(GAMEAPI)
  message(STATUS "Found GameAPI for ${MOD_NAME}: ${GAMEAPI}")
else()
  message(FATAL_ERROR "GameAPI not found for ${MOD_NAME}. Clone it in the mod's folder.")
endif()

add_library(ExampleMod SHARED
    ${GAMEAPI}/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
)

target_include_directories(ExampleMod PRIVATE
    ${MOD_NAME}/
    ${GAMEAPI}/C/
)

set_target_properties(ExampleMod PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

target_compile_definitions(ExampleMod PRIVATE
	RETRO_REVISION=${RETRO_REVISION}
	RETRO_USE_MOD_LOADER=1
	RETRO_MOD_LOADER_VER=${RETRO_MOD_LOADER_VER}
	RETRO_INCLUDE_EDITOR=$<BOOL:${MOD_INCLUDE_EDITOR}>
	MANIA_PREPLUS=$<BOOL:${MANIA_PREPLUS}>
	MANIA_FIRST_RELEASE=$<BOOL:${MANIA_FIRST_RELEASE}>
	GAME_VERSION=${GAME_VERSION}
	GAME_TYPE=1
)

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)