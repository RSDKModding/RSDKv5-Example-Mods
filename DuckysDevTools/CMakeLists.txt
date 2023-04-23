# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(DuckysDevTools)
set(MOD_NAME DuckysDevTools CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "DuckysDevTools" CACHE STRING "The name of the built library")

add_library(DuckysDevTools SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Objects/All.c
)

target_include_directories(DuckysDevTools PRIVATE
    ${MOD_NAME}/
    ${MOD_NAME}/Objects/
    GameAPI/C/
)

set_target_properties(DuckysDevTools PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)