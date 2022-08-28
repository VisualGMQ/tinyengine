#include "engine/renderer/texture.hpp"

namespace engine {

Texture::Texture(unsigned char* data, int w, int h): w_(w), h_(h) {
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

void Texture::Bind(uint32_t slot) {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id_));
}

void Texture::Unbind() {
    GL_CALL(glBindTexture(0, id_));
}


std::unordered_map<int, std::unique_ptr<Texture>> TextureFactory::textureMap_;

void TextureFactory::Init() {}

void TextureFactory::Quit() {
    textureMap_.clear();
}

Texture* TextureFactory::Create(int id, const std::string& filename) {
    int channel, w, h;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &channel, STBI_rgb_alpha);
    Texture* texture = Create(id, data, w, h);
    stbi_image_free(data);
    return texture;
}

Texture* TextureFactory::Create(int id, unsigned char* data, int w, int h) {
    if (textureMap_.find(id) != textureMap_.end()) {
        Logw("duplicate ID");
    }
    textureMap_[id] = std::make_unique<Texture>(data, w, h);
    return textureMap_[id].get();
}

Texture* TextureFactory::Find(int id) {
    auto it = textureMap_.find(id);
    if (textureMap_.end() == it) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

}
