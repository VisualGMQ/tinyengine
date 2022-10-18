include(../cmake/setup_demo.cmake)

aux_source_directory(./ PHYSICAL_SRC)
add_executable(physical ${PHYSICAL_SRC})
target_link_libraries(physical PRIVATE ${ENGINE_NAME})

CopyDLL(physical)
SetupDemoTarget(physical ${CMAKE_CURRENT_SOURCE_DIR} FALSE)