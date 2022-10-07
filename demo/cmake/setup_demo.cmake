macro(SetupDemoTarget target_name target_root_dir)
    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${target_root_dir}/resources $<TARGET_FILE_DIR:${target_name}>/resources
        COMMAND ${CMAKE_COMMAND} -E copy ${target_root_dir}/init.toml $<TARGET_FILE_DIR:${target_name}>/init.toml)

    add_custom_target(demo-${target_name}
                    COMMAND ${target_name}.exe
                    WORKING_DIRECTORY $<TARGET_FILE_DIR:${target_name}>
                    COMMENT "run ${target_name} demo")
endmacro()