#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/glhelper.hpp"

namespace engine {

/* Please make sure your image format is RGBA8888 */
class Texture final {
public:
    Texture(unsigned char* data, int w, int h);
    ~Texture();

    float Width() const { return w_; }
    float Height() const { return h_; }

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

private:
    GLuint id_;
    float w_;
    float h_;
};

class TextureFactory final {
public:
    static void Init();
    static void Quit();

    static Texture* Create(int id, const std::string& filename);
    static Texture* Create(int id, unsigned char* data, int w, int h);
    static Texture* Find(int id);

private:
    static std::unordered_map<int, std::unique_ptr<Texture>> textureMap_;
};

}
