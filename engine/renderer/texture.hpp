#pragma once

#include "engine/core/pch.hpp"
#include "engine/core/vmath.hpp"
#include "engine/core/glhelper.hpp"

namespace engine {

using TextureID = int;

/* Please make sure your image format is RGBA8888 */
class DLLEXPORT Texture final {
public:
    friend class TextureFactory;

    Texture(const std::string& name, unsigned char* data, int w, int h);
    Texture(const Texture&) = delete;
    ~Texture();

    Texture& operator=(const Texture&) = delete;

    float Width() const { return w_; }
    float Height() const { return h_; }

    void Bind(uint32_t slot = 0) const;
    void Unbind() const;

    TextureID ID() const { return myId_; }
    const std::string& Name() const { return name_; }
    Size GetSize() const { return Size(w_, h_); }

private:
    GLuint id_;
    TextureID myId_ = -1;
    std::string name_;
    float w_;
    float h_;
};

class DLLEXPORT TextureFactory final {
public:
    static void Init();
    static void Quit();

    static Texture* Create(std::string_view filename, const std::string& name);
    static Texture* Create(const std::string& name, unsigned char* data, int w, int h);
    static Texture* Find(TextureID id);
    static Texture* Find(const std::string& name);

private:
    static std::unordered_map<TextureID, std::unique_ptr<Texture>> textureMap_;
    static TextureID curId_;
};

}
