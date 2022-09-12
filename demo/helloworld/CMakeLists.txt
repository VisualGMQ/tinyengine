aux_source_directory(./ HELLOWORLD_SRC)
add_executable(helloworld ${HELLOWORLD_SRC})
target_link_libraries(helloworld PRIVATE ${ENGINE_NAME})

# under windows, copy SDL dll to build dir
if (WIN32)
    add_custom_command(
        TARGET helloworld POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_LIB_DIR}/SDL2.dll $<TARGET_FILE_DIR:helloworld>
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_TTF_LIB_DIR}/SDL2_ttf.dll $<TARGET_FILE_DIR:helloworld>
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL2_MIXER_LIB_DIR}/SDL2_mixer.dll $<TARGET_FILE_DIR:helloworld>)
endif()