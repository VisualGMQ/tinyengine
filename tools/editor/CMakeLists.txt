aux_source_directory(./src/reflect EDITOR_REFL_SRC)
aux_source_directory(./src/scenes EDITOR_SCENES_SRC)
set(EDITOR_NAME editor)
add_executable(${EDITOR_NAME}
    ${EDITOR_REFL_SRC}
    ${EDITOR_SCENES_SRC}
    ./src/main.cpp)
target_link_libraries(${EDITOR_NAME} PRIVATE meta ${ENGINE_NAME})
target_include_directories(${EDITOR_NAME} PRIVATE src)
CopyDLL(${EDITOR_NAME})
