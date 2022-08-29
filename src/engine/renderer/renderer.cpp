#include "engine/renderer/renderer.hpp"

namespace engine {

std::unique_ptr<Shader> Renderer::shader_ = nullptr;
Texture* Renderer::blackTexture_ = nullptr;
Texture* Renderer::whiteTexture_ = nullptr;
Color Renderer::currentColor_(0, 0, 0, 1);
std::unique_ptr<Mesh> Renderer::mesh_ = nullptr;
std::unique_ptr<OrthoCamera> Renderer::orthoCamera_ = nullptr;
std::unique_ptr<PerspCamera> Renderer::perspCamera_ = nullptr;
Mat4 Renderer::oldProjectMat_;
Mat4 Renderer::oldViewMat_;
Mat4 Renderer::oldModelMat_;

enum RenderInnerTextureID {
    Black = -1,
    White = -2,
};


void Renderer::Init(int orthoW, int orthoH) {
    stbi_set_flip_vertically_on_load(true);
    ShaderModule vertexModule(ReadWholeFile("shader/shader.vert"), ShaderModule::Type::Vertex);
    ShaderModule fragModule(ReadWholeFile("shader/shader.frag"), ShaderModule::Type::Fragment);
    shader_ = std::make_unique<Shader>(vertexModule, fragModule);
    unsigned char value[4] = {0x00, 0x00, 0x00, 0xFF};
    blackTexture_ = TextureFactory::Create(Black, value, 1, 1);
    memset(value, 0xFF, sizeof(unsigned char) * 4);
    whiteTexture_ = TextureFactory::Create(White, value, 1, 1);
    mesh_ = std::make_unique<Mesh>();

    orthoCamera_ = std::make_unique<OrthoCamera>(orthoW, orthoH, 1.0f);
    perspCamera_ = std::make_unique<PerspCamera>(Radians(45), 1024 / 720.0f, 0.01f, 100.f);

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::Quit() {
    shader_.reset();
    mesh_.reset();
}

void Renderer::SetClearColor(const Color& color) {
    GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::Clear() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::SetDrawColor(const Color& color) {
    shader_->Use();
    if (color != currentColor_) {
        shader_->SetVec4("color", color);
        currentColor_ = color;
    }
}

void Renderer::DrawMesh(const Mesh& mesh,
                        DrawType type,
                        const Mat4& transform,
                        Camera* camera,
                        const Texture* texture) {
    if(!camera) {
        Loge("camera not exists");
        return ;
    }

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo_));
    if (!mesh.GetIndices().empty()) {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo_));
    }
    GL_CALL(glBindVertexArray(mesh.vao_));
    shader_->Use();

    auto& project = camera->GetProject();
    auto& view = camera->GetView();
     if (transform != oldModelMat_) {
        oldModelMat_ = transform;
        shader_->SetMat4("model", transform);
    }
    if (project != oldProjectMat_) {
        oldProjectMat_ = project;
        shader_->SetMat4("project", project);
    }
    if (view != oldViewMat_) {
        oldViewMat_ = view;
        shader_->SetMat4("view", view);
    }

    texture = texture ? texture : whiteTexture_;
    texture->Bind(0);
    if (mesh.GetIndices().empty()) {
        GL_CALL(glDrawArrays(static_cast<GLenum>(type), 0, mesh.GetVertices().size()));
    } else {
        GL_CALL(glDrawElements(static_cast<GLenum>(type), mesh.GetIndices().size(), GL_UNSIGNED_INT, 0));
    }
}

void Renderer::DrawRect(const Rect& rect) {
    std::array<Vec2, 4> points{{
        Vec2(rect.position.x, rect.position.y),
        Vec2(rect.position.x + rect.size.w, rect.position.y),
        Vec2(rect.position.x + rect.size.w, rect.position.y + rect.size.h),
        Vec2(rect.position.x, rect.position.y + rect.size.h)
    }};
	auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position.Set(points[i].x, points[i].y, 0);
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    DrawMesh(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>(), orthoCamera_.get());
}

void Renderer::DrawLine(const Vec2& p1, const Vec2& p2) {
    auto& vertices = mesh_->GetVertices();
    mesh_->GetIndices().clear();
    vertices.clear();
    vertices.resize(2);
    vertices[0].position.Set(p1.x, p1.y, 0);
    vertices[1].position.Set(p2.x, p2.y, 0);
    for (auto& p : vertices) {
        p.texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    DrawMesh(*mesh_, DrawType::Lines, CreateIdentityMat<4>(), orthoCamera_.get());
}

void Renderer::FillRect(const Rect& rect) {
    auto& vertices = mesh_->GetVertices();
    mesh_->GetIndices().clear();
    vertices.clear();
    vertices.resize(6);

    Vec3 posLeftTop(rect.position.x, rect.position.y, 0),
         posRightTop(rect.position.x + rect.size.w, rect.position.y, 0),
         posRightBottom(rect.position.x + rect.size.w, rect.position.y + rect.size.h, 0),
         posLeftBottom(rect.position.x, rect.position.y + rect.size.h, 0);

    vertices[0].position = posLeftTop;
    vertices[1].position = posRightTop;
    vertices[2].position = posRightBottom;
    vertices[3] = vertices[0];
    vertices[4] = vertices[2];
    vertices[5].position = posLeftBottom;

    for (auto& p : vertices) {
        p.texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    DrawMesh(*mesh_, DrawType::Triangles, CreateIdentityMat<4>(), orthoCamera_.get());
}

void Renderer::DrawLines(const std::vector<Vec2>& points) {
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position.Set(points[i].x, points[i].y, 0);
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    DrawMesh(*mesh_, DrawType::LineStrip, CreateIdentityMat<4>(), orthoCamera_.get());
}

void Renderer::DrawTexture(const Texture& texture, Rect* src, const Rect& dst, const Color& color) {
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(6);
    mesh_->GetIndices().clear();
    Rect srcrect = src ? *src : Rect(0, 0, texture.Width(), texture.Height());

    Vec3 posLeftTop(dst.position.x, dst.position.y, 0),
         posRightTop(dst.position.x + dst.size.w, dst.position.y, 0),
         posRightBottom(dst.position.x + dst.size.w, dst.position.y + dst.size.h, 0),
         posLeftBottom(dst.position.x, dst.position.y + dst.size.h, 0);

    Vec2 texLeftTop(srcrect.position.x / texture.Width(), srcrect.position.y / texture.Height()),
         texRightTop((srcrect.position.x + srcrect.size.w) / texture.Width(), srcrect.position.y / texture.Height()),
         texRightBottom((srcrect.position.x + srcrect.size.w) / texture.Width(), (srcrect.position.y + srcrect.size.h) / texture.Height()),
         texLeftBottom(srcrect.position.x / texture.Width(), (srcrect.position.y + srcrect.size.h) / texture.Height());

    vertices[0].position = posLeftTop;
    vertices[0].texcoord = texLeftBottom;

    vertices[1].position = posRightTop;
    vertices[1].texcoord = texRightBottom;

    vertices[2].position = posLeftBottom;
    vertices[2].texcoord = texLeftTop;

    vertices[3] = vertices[1];
    vertices[4] = vertices[2];

    vertices[5].position = posRightBottom;
    vertices[5].texcoord = texRightTop;

    mesh_->Update2GPU();
    SetDrawColor(color);
    DrawMesh(*mesh_, DrawType::Triangles, CreateIdentityMat<4>(), orthoCamera_.get(), &texture);
}

}
