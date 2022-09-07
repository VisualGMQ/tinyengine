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
add_subdirectory(3rdlibs/nuklear)
add_subdirectory(3rdlibs/miniaudio)

############# build engine ##############
set(ENGINE_NAME "engine")

aux_source_directory(src/engine/core ENGINE_CORE_SRC)
aux_source_directory(src/engine/renderer ENGINE_RENDERER_SRC)
aux_source_directory(src/engine/input ENGINE_INPUT_SRC)
aux_source_directory(src/engine/ecs ENGINE_ECS_SRC)
aux_source_directory(src/engine/components ENGINE_COMPONENTS_SRC)
aux_source_directory(src/engine/UI ENGINE_UI_SRC)

add_library(${ENGINE_NAME} STATIC ${ENGINE_CORE_SRC} ${ENGINE_RENDERER_SRC} ${ENGINE_INPUT_SRC} ${ENGINE_ECS_SRC} ${ENGINE_COMPONENTS_SRC} ${ENGINE_UI_SRC})
target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw stb_image miniaudio)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
target_include_directories(${ENGINE_NAME} PUBLIC include)
target_compile_definitions(${ENGINE_NAME} PRIVATE SHOULD_EXPORT)
target_precompile_headers(${ENGINE_NAME} PUBLIC "include/engine/core/pch.hpp")

############# build game ##############
set(GAME_NAME "game")

aux_source_directory(src/game GAME_SRC)
add_executable(${GAME_NAME} ${GAME_SRC})
target_link_libraries(${GAME_NAME} PRIVATE ${ENGINE_NAME} nuklear)
target_precompile_headers(${GAME_NAME} REUSE_FROM ${ENGINE_NAME})
