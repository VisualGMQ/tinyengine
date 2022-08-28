cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    1MGames2022-2Term
    LANGUAGES CXX C
    VERSION 0.1.0
)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(3rdlibs/glfw)
add_subdirectory(3rdlibs/glad)
add_subdirectory(3rdlibs/stb)

set(AUDIO_LIB "miniaudio")

############# build engine ##############
set(ENGINE_NAME "engine")

aux_source_directory(src/engine/core ENGINE_CORE_SRC)
aux_source_directory(src/engine/renderer ENGINE_RENDERER_SRC)
aux_source_directory(src/engine/input ENGINE_INPUT_SRC)

add_library(${ENGINE_NAME} STATIC ${ENGINE_CORE_SRC} ${ENGINE_RENDERER_SRC} ${ENGINE_INPUT_SRC})
target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw stb_image)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
target_include_directories(${ENGINE_NAME} PUBLIC include)
target_compile_definitions(${ENGINE_NAME} PRIVATE SHOULD_EXPORT)
target_compile_options(
    ${ENGINE_NAME}
    PUBLIC $<$<STREQUAL:$<UPPER_CASE:"${CMAKE_BUILD_TYPE}">,"RELEASE">:-Os> -fno-rtti -fno-exceptions
)
target_precompile_headers(${ENGINE_NAME} PUBLIC "include/engine/core/pch.hpp")

if (${AUDIO_LIB} STREQUAL "miniaudio")
    add_subdirectory(3rdlibs/miniaudio)
    target_link_libraries(${ENGINE_NAME} PUBLIC miniaudio)
    message(STATUS "use miniaudio")
elseif(${AUDIO_LIB} STREQUAL "portaudio")
    add_subdirectory(3rdlibs/portaudio)
    target_link_libraries(${ENGINE_NAME} PUBLIC portaudio)
    message(STATUS "use portaudio")
else()
    message(WARNING "didn't config audio lib, your game can't play music")
endif()

############# build game ##############
set(GAME_NAME "game")

aux_source_directory(src/game GAME_SRC)
add_executable(${GAME_NAME} ${GAME_SRC})
target_link_libraries(${GAME_NAME} PRIVATE ${ENGINE_NAME})
target_precompile_headers(${GAME_NAME} REUSE_FROM ${ENGINE_NAME})
