include(../cmake/setup_demo.cmake)

aux_source_directory(src/scenes SCENES_SRC)
aux_source_directory(src/scripts SCRIPTS_SRC)

set(DEMO_NAME small_man)

add_executable(${DEMO_NAME})
target_sources(${DEMO_NAME} PRIVATE
                ${SCRIPTS_SRC}
                ${SCENES_SRC}
                src/main.cpp
)
target_link_libraries(${DEMO_NAME} PRIVATE tinyengine)
target_precompile_headers(${DEMO_NAME} REUSE_FROM tinyengine)
target_include_directories(${DEMO_NAME} PRIVATE src)

CopyDLL(${DEMO_NAME})
SetupDemoTarget(${DEMO_NAME} ${CMAKE_CURRENT_SOURCE_DIR} TRUE)