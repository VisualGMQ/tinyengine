#include "engine/renderer/texture.hpp"

namespace engine {

Texture::Texture(unsigned char* data, int w, int h): size_(w, h) {
	GL_CALL(glGenTextures(1, &id_));
	GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));   
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	if (data) {
		GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
	} else {
		Loge("texture create failed, data == nullptr");
	}
}

Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &id_));
}

void Texture::Bind(uint32_t slot) const {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
}

void Texture::Unbind() const {
    GL_CALL(glBindTexture(0, id_));
}


std::vector<std::unique_ptr<Texture>> TextureFactory::textures_;
TextureID TextureFactory::curId_ = 0;

void TextureFactory::Init() {}

void TextureFactory::Quit() {
    textures_.clear();
}

Texture* TextureFactory::Create(const std::string& filename) {
    int channel, w, h;
    SDL_Surface* surface = IMG_Load(filename.data());
    SDL_Surface* cvtSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    unsigned char* data = (unsigned char*)cvtSurface->pixels;
    textures_.push_back(std::make_unique<Texture>(data, cvtSurface->w, cvtSurface->h));
    auto& texture = textures_.back();
    w = cvtSurface->w;
    h = cvtSurface->h;
    SDL_FreeSurface(cvtSurface);
    texture->myId_ = curId_++;
    return texture.get();
}

Texture* TextureFactory::Create(unsigned char* data, int w, int h) {
    textures_.push_back(std::make_unique<Texture>(data, w, h));
    auto& texture = textures_.back();
    texture->myId_ = curId_++;
    return texture.get();
}

Texture* TextureFactory::CreateFromXpm(char** xpmData) {
    SDL_Surface* surface = IMG_ReadXPMFromArray(xpmData);
    SDL_Surface* cvtSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
    SDL_FreeSurface(surface);
    unsigned char* data = (unsigned char*)cvtSurface->pixels;
    textures_.push_back(std::make_unique<Texture>(data, cvtSurface->w, cvtSurface->h));
    auto& texture = textures_.back();
    SDL_FreeSurface(cvtSurface);
    texture->myId_ = curId_++;
    return texture.get();
}

}
