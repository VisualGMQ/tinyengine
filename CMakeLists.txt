cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    TinyEngine
    LANGUAGES CXX C
    VERSION 0.1.0
)

include(cmake/FindSDL2.cmake)
include(cmake/FindSDL2_mixer.cmake)
include(cmake/FindSDL2_ttf.cmake) 
add_subdirectory(3rdlibs/glad)
add_subdirectory(3rdlibs/stb)
add_subdirectory(3rdlibs/nuklear)

include(cmake/shader2inc.cmake)
include(cmake/copydll.cmake)

############# build options ##############
option(ENGINE_BUILD_DEMOS "do you want to build demos" OFF)

############# build engine ##############
set(ENGINE_NAME "tinyengine")

Shader2Inc()

aux_source_directory(src/core ENGINE_CORE_SRC)
aux_source_directory(src/renderer ENGINE_RENDERER_SRC)
aux_source_directory(src/input ENGINE_INPUT_SRC)
aux_source_directory(src/ecs ENGINE_ECS_SRC)
aux_source_directory(src/ui ENGINE_UI_SRC)
aux_source_directory(src/sound ENGINE_SOUND_SRC)
aux_source_directory(src/debug ENGINE_DEBUG_SRC)

add_library(${ENGINE_NAME} STATIC)
target_sources(${ENGINE_NAME} PRIVATE
                ${ENGINE_CORE_SRC}
                ${ENGINE_RENDERER_SRC}
                ${ENGINE_INPUT_SRC}
                ${ENGINE_ECS_SRC}
                ${ENGINE_UI_SRC}
                ${ENGINE_SOUND_SRC}
                ${ENGINE_DEBUG_SRC}
                src/entry.cpp)
target_link_libraries(${ENGINE_NAME} PUBLIC glad SDL2 SDL2_ttf SDL2_mixer nuklear stb_image)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
target_include_directories(${ENGINE_NAME} PUBLIC ./)
target_precompile_headers(${ENGINE_NAME} PUBLIC "engine/core/pch.hpp")

############# build demo ##############
if (${ENGINE_BUILD_DEMOS})
    add_subdirectory(demo)
endif()
