# Basic CMake that uses All.c
cmake_minimum_required(VERSION 3.7)

project(MaxControl)
set(MOD_NAME MaxControl CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "MaxControl" CACHE STRING "The name of the built library")

add_library(MaxControl SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
)

target_include_directories(MaxControl PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(MaxControl PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)