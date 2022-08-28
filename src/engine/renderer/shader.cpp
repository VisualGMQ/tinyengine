#include "engine/renderer/shader.hpp"

namespace engine {


ShaderModule::ShaderModule(const std::string& source_code, Type type) {
    id_ = glCreateShader(type);
    const char* code = source_code.c_str();
    GL_CALL(glShaderSource(id_, 1, &code, nullptr));
    GL_CALL(glCompileShader(id_));
    int  isSuccess;
    char infoLog[1024];
    GL_CALL(glGetShaderiv(id_, GL_COMPILE_STATUS, &isSuccess));
    if (!isSuccess) {
        glGetShaderInfoLog(id_, sizeof(infoLog), NULL, infoLog);
        Loge("vertex shader compile failed:\n%s", infoLog);
    }
}

ShaderModule::~ShaderModule() {
    GL_CALL(glDeleteShader(id_));
}


Shader::Shader(const ShaderModule& vertex, const ShaderModule& fragment) {
    program_ = glCreateProgram();
    GL_CALL(glAttachShader(program_, vertex.GetID()));
    GL_CALL(glAttachShader(program_, fragment.GetID()));
    GL_CALL(glLinkProgram(program_));

    int isSuccess;
    char infoLog[1024];
    GL_CALL(glGetProgramiv(program_, GL_LINK_STATUS, &isSuccess));
    if(!isSuccess) {
        glGetProgramInfoLog(program_, sizeof(infoLog), NULL, infoLog);
        Loge("shader link failed:\n%s", infoLog);
    }
}

Shader::~Shader() {
    GL_CALL(glDeleteProgram(program_));
}

void Shader::Use() const {
    GL_CALL(glUseProgram(program_));
}

void Shader::SetVec4(const std::string& name, const Vec4& v) {
    if (auto loc = findLocation(name); loc >= 0) {
        GL_CALL(glUniform4f(loc, v.x, v.y, v.z, v.w));
    }
}

void Shader::SetVec3(const std::string& name, const Vec3& v) {
    if (auto loc = findLocation(name); loc >= 0) {
        GL_CALL(glUniform3f(loc, v.x, v.y, v.z));
    }
}

void Shader::SetVec2(const std::string& name, const Vec2& v) {
    if (auto loc = findLocation(name); loc >= 0) {
        GL_CALL(glUniform2f(loc, v.x, v.y));
    }
}

void Shader::SetMat4(const std::string& name, const Mat4& m) {
    if (auto loc = findLocation(name); loc >= 0) {
        GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, m.Data()));
    }
}

GLint Shader::findLocation(const std::string& name) {
    GLint loc = glGetUniformLocation(program_, name.c_str());
    if (loc < 0) {
        Loge("get uniform `%s` location failed", name.c_str());
    }
    return loc;
}

}
