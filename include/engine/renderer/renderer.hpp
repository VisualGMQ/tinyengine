#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"
#include "engine/renderer/mesh.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/camera.hpp"

namespace engine {

enum class DrawType {
    Triangles = GL_TRIANGLES,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    LineLoop = GL_LINE_LOOP,
    Fans = GL_TRIANGLE_FAN,
};

class Renderer final {
public:
    static void Init(int orthoW, int orthoH);
    static void Quit();

    static void SetClearColor(const Color&);
    static void Clear();
    static void SetDrawColor(const Color&);

    // 3D draw functions
    static void DrawMesh(const Mesh&, DrawType, const Mat4&, Camera* camera, Texture* texture = nullptr);

    // 2D draw functions
    static void DrawRect(const Rect&);
    static void DrawLine(const Vec2& p1, const Vec2& p2);

    static void DrawLines(const std::vector<Vec2>& points);

    template <size_t N>
    static void DrawLines(const std::array<Vec2, N>& points) {
        auto& vertices = mesh_->GetVertices();
        vertices.clear();
        vertices.resize(N);
        for (int i = 0; i < N; i++) {
            vertices[i].position.Set(points[i].x, points[i].y, 0);
            vertices[i].texcoord.Set(0, 0);
        }
        mesh_->Update2GPU();
        DrawMesh(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>(), orthoCamera_.get());
    }

    static void FillRect(const Rect& rect);
    static void DrawTexture(const Texture& texture, Rect* src, Rect* dst);

private:
    static std::unique_ptr<Shader> shader_;
    static std::string readWholeFile(const std::string&);
    
    static Texture* blackTexture_;
    static Texture* whiteTexture_;
    static Color currentColor_;
    static std::unique_ptr<Mesh> mesh_;
    static std::unique_ptr<OrthoCamera> orthoCamera_;
    static std::unique_ptr<PerspCamera> perspCamera_;
    static std::unique_ptr<EmptyCamera> emptyCamera_;

    // some staging state
    static Mat4 oldProjectMat_;
    static Mat4 oldViewMat_;
    static Mat4 oldModelMat_;
};

}
