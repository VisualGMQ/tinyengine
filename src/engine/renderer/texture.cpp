#include "engine/renderer/texture.hpp"

namespace engine {

Texture::Texture(const std::string& name, unsigned char* data, int w, int h): name_(name), w_(w), h_(h) {
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


std::unordered_map<TextureID, std::unique_ptr<Texture>> TextureFactory::textureMap_;
TextureID TextureFactory::curId_ = 0;

void TextureFactory::Init() {}

void TextureFactory::Quit() {
    textureMap_.clear();
}

Texture* TextureFactory::Create(const std::string& filename, const std::string& name) {
    int channel, w, h;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &channel, STBI_rgb_alpha);
    auto texture = std::make_unique<Texture>(name, data, w, h);
    stbi_image_free(data);
    TextureID id = curId_++;
    texture->myId_ = id;
    Texture* result = texture.get();
    textureMap_[id] = std::move(texture);
    return result;
}

Texture* TextureFactory::Create(const std::string& name, unsigned char* data, int w, int h) {
    auto texture = std::make_unique<Texture>(name, data, w, h);
    TextureID id = curId_++;
    texture->myId_ = id;
    Texture* result = texture.get();
    textureMap_[id] = std::move(texture);
    return result;
}

Texture* TextureFactory::Find(TextureID id) {
    auto it = textureMap_.find(id);
    if (textureMap_.end() == it) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

Texture* TextureFactory::Find(const std::string& name) {
    for (auto& [key, value] : textureMap_) {
        if (value->Name() == name) {
            return value.get();
        }
    }
    return nullptr;
}

}
