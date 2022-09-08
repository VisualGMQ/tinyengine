cmake_minimum_required(VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    TinyEngine
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

############# build options ##############
option(ENGINE_BUILD_DEMOS "do you want to build demos" OFF)

############# build engine ##############
set(ENGINE_NAME "tinyengine")

aux_source_directory(src/core ENGINE_CORE_SRC)
aux_source_directory(src/renderer ENGINE_RENDERER_SRC)
aux_source_directory(src/input ENGINE_INPUT_SRC)
aux_source_directory(src/ecs ENGINE_ECS_SRC)
aux_source_directory(src/components ENGINE_COMPONENTS_SRC)
aux_source_directory(src/UI ENGINE_UI_SRC)

add_library(${ENGINE_NAME} STATIC)
target_sources(${ENGINE_NAME} PRIVATE ${ENGINE_CORE_SRC} ${ENGINE_RENDERER_SRC} ${ENGINE_INPUT_SRC} ${ENGINE_ECS_SRC} ${ENGINE_COMPONENTS_SRC} ${ENGINE_UI_SRC})
target_link_libraries(${ENGINE_NAME} PUBLIC glad glfw stb_image miniaudio)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
target_include_directories(${ENGINE_NAME} PUBLIC ./)
target_compile_definitions(${ENGINE_NAME} PUBLIC SHOULD_EXPORT)
target_precompile_headers(${ENGINE_NAME} PUBLIC "engine/core/pch.hpp")

############# build demo ##############
if (${ENGINE_BUILD_DEMOS})
    add_subdirectory(demo)
endif()
