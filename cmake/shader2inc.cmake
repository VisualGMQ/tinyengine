function(Shader2Inc)
    set(INC_FILENAME ${CMAKE_SOURCE_DIR}/shader.inc)

    file(STRINGS ${CMAKE_SOURCE_DIR}/shader/shader.vert VERTEX_SHADER_SOURCE NEWLINE_CONSUME)
    file(WRITE  ${INC_FILENAME} "std::string VertexShaderSource = R\"(\n")
    file(APPEND ${INC_FILENAME} ${VERTEX_SHADER_SOURCE})
    file(APPEND ${INC_FILENAME} ")\";\n")

    file(STRINGS ${CMAKE_SOURCE_DIR}/shader/shader.frag FRAG_SHADER_SOURCE NEWLINE_CONSUME)
    file(APPEND ${INC_FILENAME} "\nstd::string FragShaderSource = R\"(\n")
    file(APPEND ${INC_FILENAME} ${FRAG_SHADER_SOURCE})
    file(APPEND ${INC_FILENAME} ")\";\n")
endfunction(Shader2Inc)