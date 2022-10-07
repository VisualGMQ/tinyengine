include(../cmake/setup_demo.cmake)

aux_source_directory(./src HELLOWORLD_SRC)
add_executable(helloworld ${HELLOWORLD_SRC})
target_link_libraries(helloworld PRIVATE ${ENGINE_NAME})

CopyDLL(helloworld)
SetupDemoTarget(helloworld ${CMAKE_CURRENT_SOURCE_DIR})