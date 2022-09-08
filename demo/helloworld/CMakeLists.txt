aux_source_directory(./ HELLOWORLD_SRC)
add_executable(helloworld ${HELLOWORLD_SRC})
target_link_libraries(helloworld PRIVATE ${ENGINE_NAME})