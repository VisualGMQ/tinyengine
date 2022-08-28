#pragma once

#include "engine/core/vmath.hpp"
#include "engine/core/pch.hpp"
#include "engine/core/glhelper.hpp"

namespace engine {

class Vertex final {
public:
    Vec3 position;
    Vec2 texcoord;

    Vertex() = default;
    Vertex(const Vec3& position): position(position) {}
    Vertex(const Vec3& position, const Vec2& texcoord): position(position), texcoord(texcoord) {}
};

class Mesh final {
public:
    friend class Renderer;

    Mesh();
    Mesh(const std::initializer_list<Vertex>&);
    Mesh(const std::initializer_list<Vertex>&, const std::initializer_list<uint32_t>&);
    Mesh(const std::vector<Vertex>&);
    Mesh(const std::vector<Vertex>&, const std::vector<uint32_t>&);
    ~Mesh();

    std::vector<Vertex>& GetVertices() { return vertices_; }
    std::vector<uint32_t>& GetIndices() { return indices_; }
    const std::vector<Vertex>& GetVertices() const { return vertices_; }
    const std::vector<uint32_t>& GetIndices() const { return indices_; }
    void Update2GPU();

// private:
    std::vector<Vertex> vertices_;
    std::vector<uint32_t> indices_;
    GLuint vao_;
    GLuint vbo_;
    GLuint ebo_;
};

}
