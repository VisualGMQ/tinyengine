#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/glhelper.hpp"
#include "engine/renderer/image.hpp"

namespace engine {

using TextureID = int;

/* Please make sure your image format is RGBA8888 */
class DLLEXPORT Texture final {
public:
    friend class TextureFactory;

    Texture(unsigned char* data, int w, int h);
    Texture(const Texture&) = delete;
    ~Texture();

    Texture& operator=(const Texture&) = delete;

    float Width() const { return size_.w; }
    float Height() const { return size_.h; }

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    TextureID ID() const { return myId_; }
    GLuint GLID() const { return id_; }
    Size GetSize() const { return size_; }

private:
    GLuint id_;
    TextureID myId_ = -1;
    Size size_;
};

class DLLEXPORT TextureFactory final {
public:
    static void Init();
    static void Quit();

    static Texture* Create(const std::string& filename);
    static Texture* Create(unsigned char* data, int w, int h);
    static Texture* CreateFromXpm(char** xpmData);

private:
    static std::vector<std::unique_ptr<Texture>> textures_;
    static TextureID curId_;
};

}
