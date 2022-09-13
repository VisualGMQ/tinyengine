#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/tool.hpp"
#include "engine/renderer/mesh.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/renderer/texture.hpp"
#include "engine/renderer/camera.hpp"
#include "engine/renderer/font.hpp"

namespace engine {

enum class DLLEXPORT DrawType {
    Triangles = GL_TRIANGLES,
    Lines = GL_LINES,
    LineStrip = GL_LINE_STRIP,
    LineLoop = GL_LINE_LOOP,
    Fans = GL_TRIANGLE_FAN,
};

class DLLEXPORT Renderer final {
public:
    Renderer() = delete;

    static void Init(int w, int h);
    static void Quit();

    // for nuklear GUI
    static void ResestState();

    static void SetClearColor(const Color&);
    static void Clear();
    static void SetDrawColor(const Color&);

    static void SetOrthoCamera(const std::shared_ptr<OrthoCamera>&);
    static void SetPerspCamera(const std::shared_ptr<PerspCamera>&);
    static std::shared_ptr<OrthoCamera>& GetOrthoCamera();
    static std::shared_ptr<PerspCamera>& GetPerspCamera();

    static void Begin2D();
    static void Begin3D();

    // 3D draw functions
    static void DrawMeshFrame(const Mesh&, const Mat4&, const Texture* = nullptr);
    static void DrawMeshSolid(const Mesh&, const Mat4&, const Texture* = nullptr);
    static void DrawLine(const Vec3&, const Vec3&);
    static void DrawLines(const std::vector<Vec3>&);
    static void DrawLineLoop(const std::vector<Vec3>&);

    // for debug, for location
    static void DrawGrid();

    // 2D draw functions
    static void DrawRect(const Rect&);
    static void DrawLine(const Vec2&, const Vec2&);

    static void DrawLines(const std::vector<Vec2>&);
    static void DrawLineLoop(const std::vector<Vec2>&);

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
        drawMeshSolid(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>(), orthoCamera_.get());
    }

    static void FillRect(const Rect& rect);
    static void DrawTexture(const Texture& texture, Rect* src, const Size& size, const Mat4& transform = CreateIdentityMat<4>());
    static void DrawText(Font* font, const std::string& text, const Vec2& pos);

private:
    static std::unique_ptr<Shader> shader_;
    
    static Texture* blackTexture_;
    static Texture* whiteTexture_;
    static Color currentColor_;
    static std::unique_ptr<Mesh> mesh_;
    static std::shared_ptr<OrthoCamera> orthoCamera_;
    static std::shared_ptr<PerspCamera> perspCamera_;
    static Camera* camera_;

    // some staging state
    static Mat4 oldProjectMat_;
    static Mat4 oldViewMat_;
    static Mat4 oldModelMat_;
    static GLenum oldPolygonMode_;

    static void drawMesh(const Mesh&, DrawType, const Mat4&, const Texture* texture);
    static void drawMeshFrame(const Mesh&, DrawType, const Mat4&, const Texture* = nullptr);
    static void drawMeshSolid(const Mesh&, DrawType, const Mat4&, const Texture* = nullptr);
};

}
