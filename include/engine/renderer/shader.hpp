#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/glhelper.hpp"
#include "engine/core/vmath.hpp"

namespace engine {

class DLLEXPORT ShaderModule final {
public:
    enum Type {
        Vertex = GL_VERTEX_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
    };

    ShaderModule(const std::string& source_code, Type type);
    ~ShaderModule();

    GLuint GetID() const { return id_; }

private:
    GLuint id_;
};

class DLLEXPORT Shader final {
public:
    Shader(const ShaderModule& vertex, const ShaderModule& fragment);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader();

    void Use() const;

    void SetVec4(const std::string& name, const Vec4&);
    void SetVec3(const std::string& name, const Vec3&);
    void SetVec2(const std::string& name, const Vec2&);
    void SetMat4(const std::string& name, const Mat4&);

private:
    GLuint program_;

    GLint findLocation(const std::string&);
};

}
