#include "engine/renderer/mesh.hpp"

namespace engine {

Mesh::Mesh() {
    GL_CALL(glGenBuffers(1, &vbo_));
    GL_CALL(glGenBuffers(1, &ebo_));
    GL_CALL(glGenVertexArrays(1, &vao_));
}

Mesh::Mesh(const std::initializer_list<Vertex>& vertices): Mesh() {
    vertices_ = vertices;
    Update2GPU();
}

Mesh::Mesh(const std::initializer_list<Vertex>& vertices, const std::initializer_list<uint32_t>& indices)
    : Mesh() {
    vertices_ = vertices;
    indices_ = indices;
    Update2GPU();
}

Mesh::Mesh(const std::vector<Vertex>& vertices): Mesh() {
    vertices_ = vertices;
    Update2GPU();
}

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices): Mesh() {
    vertices_ = vertices;
    indices_ = indices;
    Update2GPU();
}

void Mesh::Update2GPU() {
    GL_CALL(glBindVertexArray(vao_));

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo_));
    if (!vertices_.empty()) {
        GL_CALL(glBufferData(GL_ARRAY_BUFFER,
                             vertices_.size() * sizeof(Vertex), vertices_.data(),
                             GL_STATIC_DRAW));
    }

    GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_));
    if (!indices_.empty()) {
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             indices_.size() * sizeof(uint32_t),
                             indices_.data(),
                             GL_STATIC_DRAW));
    }

    GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, 0));
    GL_CALL(glEnableVertexAttribArray(0));
    GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (void*)(sizeof(GLfloat) * 3)));
    GL_CALL(glEnableVertexAttribArray(1));
}

Mesh::~Mesh() {
    GL_CALL(glDeleteVertexArrays(1, &vao_));
    GL_CALL(glDeleteBuffers(1, &vbo_));
    GL_CALL(glDeleteBuffers(1, &ebo_));
}

std::shared_ptr<Mesh> CreateCubeMesh() {
    return std::shared_ptr<Mesh>(new Mesh({
            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 0.0f)),
            Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 0.0f)),

            Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
            Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),

            Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),
            Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 1.0f, 1.0f)),
            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
            Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 1.0f, 0.0f)),

            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(0.0f, 1.0f)),
            Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(0.0f, 1.0f)),
            Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(0.0f, 0.0f)),
            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 0.0f)),

            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(0.5f, -0.5f, -0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(0.5f, -0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(-0.5f, -0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
            Vertex(Vec3(-0.5f, -0.5f, -0.5f), Vec2( 0.0f, 1.0f)),

            Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
            Vertex(Vec3(0.5f,  0.5f, -0.5f), Vec2(1.0f, 1.0f)),
            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(0.5f,  0.5f,  0.5f), Vec2(1.0f, 0.0f)),
            Vertex(Vec3(-0.5f,  0.5f,  0.5f), Vec2( 0.0f, 0.0f)),
            Vertex(Vec3(-0.5f,  0.5f, -0.5f), Vec2( 0.0f, 1.0f)),
    }));
}

std::shared_ptr<Mesh> CreateTriangularPyramidMesh() {
    float sqrt3 = std::sqrt(3),
          sqrt13 = std::sqrt(13);
    return std::shared_ptr<Mesh>(new Mesh({
            Vertex(Vec3(-0.5, -sqrt13 / 16.0, sqrt3 / 6.0)),
            Vertex(Vec3(0.5, -sqrt13 / 16.0, sqrt3 / 6.0)),
            Vertex(Vec3(0, -sqrt13 / 16.0, -sqrt3 / 6.0)),
            Vertex(Vec3(0, 3 * sqrt13 / 16.0, 0)),
            },
            {
                0, 1, 3,
                1, 2, 3,
                2, 0, 3,
                0, 1, 2,
            }));
}

}