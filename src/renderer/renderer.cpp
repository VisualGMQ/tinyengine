#include "engine/renderer/renderer.hpp"

#ifndef IS_DEBUG
#include "shader.inc"
#endif

namespace engine {

std::unique_ptr<Shader> Renderer::shader_ = nullptr;
Texture* Renderer::blackTexture_ = nullptr;
Texture* Renderer::whiteTexture_ = nullptr;
Color Renderer::currentColor_(0, 0, 0, 1);
std::unique_ptr<Mesh> Renderer::mesh_ = nullptr;
std::shared_ptr<OrthoCamera> Renderer::orthoCamera_ = nullptr;
std::shared_ptr<PerspCamera> Renderer::perspCamera_ = nullptr;
Mat4 Renderer::oldProjectMat_;
Mat4 Renderer::oldViewMat_;
Mat4 Renderer::oldModelMat_;
GLenum Renderer::oldPolygonMode_ = GL_FILL;
Camera* Renderer::camera_ = nullptr;
Color Renderer::keyColor_ = engine::Color(1, 1, 1);

void Renderer::Init(int w, int h) {
    if (TTF_Init() != 0) {
        Loge("SDL ttf init failed: {}", TTF_GetError());
    }
    if (IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF) == 0) {
        Loge("SDL image init failed: {}", IMG_GetError());
    }
#ifdef IS_DEBUG
    ShaderModule vertexModule(ReadWholeFile("shader/shader.vert"), ShaderModule::Type::Vertex);
    ShaderModule fragModule(ReadWholeFile("shader/shader.frag"), ShaderModule::Type::Fragment);
#else
    ShaderModule vertexModule(VertexShaderSource, ShaderModule::Type::Vertex);
    ShaderModule fragModule(FragShaderSource, ShaderModule::Type::Fragment);
#endif
    shader_ = std::make_unique<Shader>(vertexModule, fragModule);
    unsigned char value[4] = {0x00, 0x00, 0x00, 0xFF};
    blackTexture_ = TextureFactory::Create(value, 1, 1);
    memset(value, 0xFF, sizeof(unsigned char) * 4);
    whiteTexture_ = TextureFactory::Create(value, 1, 1);
    mesh_ = std::make_unique<Mesh>();

    orthoCamera_ = std::make_unique<OrthoCamera>(w, h, -1.1, 1.1);
    perspCamera_ = std::make_unique<PerspCamera>(Radians(45), w / h, 0.1f, 100.f);

    shader_->Use();
    shader_->SetVec4("keycolor", keyColor_);
}

void Renderer::ResestState() {
    // GL_CALL(glEnable(GL_BLEND));
    // GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void Renderer::Quit() {
    IMG_Quit();
    TTF_Quit();
    shader_.reset();
    mesh_.reset();
}

void Renderer::SetClearColor(const Color& color) {
    GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::Clear() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT));
}


void Renderer::SetKeyColor(const engine::Color& keycolor) {
    if (keycolor != keyColor_) {
        keyColor_ = keycolor;
        shader_->SetVec4("keycolor", keyColor_);
    }
}

void Renderer::SetDrawColor(const Color& color) {
    shader_->Use();
    if (color != currentColor_) {
        shader_->SetVec4("color", color);
        currentColor_ = color;
    }
}

void Renderer::SetOrthoCamera(const std::shared_ptr<OrthoCamera>& camera) {
    orthoCamera_ = camera;
}

void Renderer::SetPerspCamera(const std::shared_ptr<PerspCamera>& camera) {
    perspCamera_ = camera;
}

std::shared_ptr<OrthoCamera>& Renderer::GetOrthoCamera() {
    return orthoCamera_;
}

std::shared_ptr<PerspCamera>& Renderer::GetPerspCamera() {
    return perspCamera_;
}

void Renderer::Begin2D() {
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glDisable(GL_CULL_FACE));
    camera_ = orthoCamera_.get();
}

void Renderer::Begin3D() {
    GL_CALL(glEnable(GL_DEPTH_TEST));
    GL_CALL(glEnable(GL_CULL_FACE));
    camera_ = perspCamera_.get();
}

void Renderer::DrawMeshSolid(const Mesh& mesh, const Mat4& transform, const Texture* texture) {
    drawMeshSolid(mesh, DrawType::Triangles, transform, texture);
}

void Renderer::DrawMeshFrame(const Mesh& mesh, const Mat4& transform, const Texture* texture) {
    drawMeshFrame(mesh, DrawType::Triangles, transform, texture);
}

void Renderer::drawMesh(const Mesh& mesh,
                        DrawType type,
                        const Mat4& transform,
                        const Texture* texture) {
    if(!camera_) {
        Loge("camera not exists");
        return ;
    }

    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo_));
    if (!mesh.GetIndices().empty()) {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo_));
    }
    GL_CALL(glBindVertexArray(mesh.vao_));
    shader_->Use();

    auto& project = camera_->Project();
    auto& view = camera_->View();
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

void Renderer::drawMeshFrame(const Mesh& mesh, DrawType type, const Mat4& transform, const Texture* texture) {
    if (oldPolygonMode_ != GL_LINE) {
        GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
        oldPolygonMode_ = GL_LINE;
    }
    drawMesh(mesh, type, transform, texture);
}

void Renderer::drawMeshSolid(const Mesh& mesh, DrawType type, const Mat4& transform, const Texture* texture) {
    if (oldPolygonMode_ != GL_FILL) {
        GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
        oldPolygonMode_ = GL_FILL;
    }
    drawMesh(mesh, type, transform, texture);
}

const Color NoneKeyColor(-1, -1, -1);

void Renderer::DrawLine(const Vec3& p1, const Vec3& p2) {
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    mesh_->GetIndices().clear();
    vertices.resize(2);
    vertices[0].position = p1;
    vertices[0].texcoord.Set(0, 0);
    vertices[1].position = p2;
    vertices[1].texcoord.Set(0, 0);
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::Lines, CreateIdentityMat<4>());
}

void Renderer::DrawGrid() {
    Renderer::SetKeyColor(NoneKeyColor);
    for (int i = -100; i <= 100; i++) {
        DrawLine(Vec3(i * 1, 0, -100), Vec3(i * 1, 0, 100));
        DrawLine(Vec3(-100, 0, i * 1), Vec3(100, 0, i * 1));
    }
}

void Renderer::DrawRect(const Rect& rect, float zIndex) {
    Renderer::SetKeyColor(NoneKeyColor);
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
        vertices[i].position.Set(points[i].x, points[i].y, zIndex);
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>());
}

void Renderer::DrawLine(const Vec2& p1, const Vec2& p2, float zIndex) {
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    mesh_->GetIndices().clear();
    vertices.clear();
    vertices.resize(2);
    vertices[0].position.Set(p1.x, p1.y, zIndex);
    vertices[1].position.Set(p2.x, p2.y, zIndex);
    for (auto& p : vertices) {
        p.texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::Lines, CreateIdentityMat<4>());
}

void Renderer::DrawLines(const std::vector<Vec3>& points) {
    if (points.empty()) return;
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position = points[i];
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::LineStrip, CreateIdentityMat<4>());
}

void Renderer::DrawLineLoop(const std::vector<Vec3>& points) {
    if (points.empty()) return;
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position = points[i];
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>());
}

void Renderer::FillRect(const Rect& rect, float zIndex) {
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    mesh_->GetIndices().clear();
    vertices.clear();
    vertices.resize(6);

    Vec3 posLeftTop(rect.position.x, rect.position.y, zIndex),
         posRightTop(rect.position.x + rect.size.w, rect.position.y, zIndex),
         posRightBottom(rect.position.x + rect.size.w, rect.position.y + rect.size.h, zIndex),
         posLeftBottom(rect.position.x, rect.position.y + rect.size.h, zIndex);

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
    drawMeshSolid(*mesh_, DrawType::Triangles, CreateIdentityMat<4>());
}

void Renderer::DrawLines(const std::vector<Vec2>& points, float zIndex) {
    if (points.empty()) return;
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position.Set(points[i].x, points[i].y, zIndex);
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::LineStrip, CreateIdentityMat<4>());
}

void Renderer::DrawLineLoop(const std::vector<Vec2>& points, float zIndex) {
    if (points.empty()) return;
    Renderer::SetKeyColor(NoneKeyColor);
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(points.size());
    for (int i = 0; i < points.size(); i++) {
        vertices[i].position.Set(points[i].x, points[i].y, zIndex);
        vertices[i].texcoord.Set(0, 0);
    }
    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::LineLoop, CreateIdentityMat<4>());
}

void Renderer::DrawTexture(const Texture& texture, Rect* src, const Size& size, const Mat4& transform, float zIndex) {
    auto& vertices = mesh_->GetVertices();
    vertices.clear();
    vertices.resize(6);
    mesh_->GetIndices().clear();
    Rect srcrect = src ? *src : Rect(0, 0, texture.Width(), texture.Height());

    float half_w = size.w / 2.0,
          half_h = size.h / 2.0;
    Vec3 posLeftTop(-half_w, -half_h, zIndex),
         posRightTop(half_w, -half_h, zIndex),
         posRightBottom(half_w, half_h, zIndex),
         posLeftBottom(-half_w, half_h, zIndex);

    Vec2 texLeftBottom(srcrect.position.x / texture.Width(), srcrect.position.y / texture.Height()),
         texRightTop((srcrect.position.x + srcrect.size.w) / texture.Width(), (srcrect.position.y + srcrect.size.h) / texture.Height()),
         texRightBottom((srcrect.position.x + srcrect.size.w) / texture.Width(), srcrect.position.y / texture.Height()),
         texLeftTop(srcrect.position.x / texture.Width(), (srcrect.position.y + srcrect.size.h) / texture.Height());

    vertices[0].position = posLeftTop;
    vertices[0].texcoord = texLeftBottom;

    vertices[1].position = posRightTop;
    vertices[1].texcoord = texRightBottom;

    vertices[2].position = posLeftBottom;
    vertices[2].texcoord = texLeftTop;

    vertices[3] = vertices[2];
    vertices[4] = vertices[1];

    vertices[5].position = posRightBottom;
    vertices[5].texcoord = texRightTop;

    mesh_->Update2GPU();
    drawMeshSolid(*mesh_, DrawType::Triangles, transform, &texture);
}

void Renderer::DrawText(Font* font, const std::string& text, const Vec2& pos, float zIndex) {
    if (!font) return;
    Renderer::SetKeyColor(Color{0, 0, 0});

    SDL_Surface* surface = TTF_RenderUTF8_Shaded(font->font_, text.c_str(), SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255});
    SDL_Surface* cvtSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);

    Texture texture((unsigned char*)cvtSurface->pixels, cvtSurface->w, cvtSurface->h);

    texture.Bind();
    DrawTexture(texture,
                nullptr,
                Size(cvtSurface->w, cvtSurface->h),
                CreateTranslate(Vec3(pos.x, pos.y + cvtSurface->h / 2.0f, 0)) *
                CreateScale(Vec3(1, 1, 1)));

    SDL_FreeSurface(cvtSurface);
}

}
