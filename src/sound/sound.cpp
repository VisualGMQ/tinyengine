#include "engine/sound/sound.hpp"

namespace engine {

ma_engine Sound::engine_;

void Sound::Init() {
    auto result = ma_engine_init(NULL, &engine_);
    if (result != MA_SUCCESS) {
        Loge("sound engine init failed");
    }
}

void Sound::Quit() {
    ma_engine_uninit(&engine_);
}

void Sound::PlaySound(const std::string& filename) {
    ma_engine_play_sound(&engine_, filename.c_str(), nullptr);
}

Sound::Sound(SoundID id, const std::string& filename, const std::string& name, bool async, bool is3D): id_(id), name_(name) {
    if (ma_sound_init_from_file(&engine_,
                                filename.c_str(),
                                MA_SOUND_FLAG_DECODE | (async ? MA_SOUND_FLAG_ASYNC: 0),
                                nullptr, nullptr, &sound_) != MA_SUCCESS) {
        Loge("sound {} load failed", filename);
    } else {
        ma_sound_set_spatialization_enabled(&sound_, is3D);
    }
}

Sound::~Sound() {
    ma_sound_uninit(&sound_);
}

void Sound::Play() {
    ma_sound_start(&sound_);
}

void Sound::Stop() {
    ma_sound_stop(&sound_);
}

void Sound::SetPosition(const Vec3& position) {
    ma_sound_set_position(&sound_, position.x, position.y, position.z);
}

void Sound::SetDirection(const Vec3& dir) {
    ma_sound_set_direction(&sound_, dir.x, dir.y, dir.z);
}

void Sound::SetVelocity(const Vec3& vel) {
    ma_sound_set_velocity(&sound_, vel.x, vel.y, vel.z);
}

void Sound::FadeIn(int milliseconds) {
    ma_sound_set_fade_in_milliseconds(&sound_, 0, 1, milliseconds);
}

void Sound::FadeOut(int milliseconds) {
    ma_sound_set_fade_in_milliseconds(&sound_, -1, 0, milliseconds);
}

bool Sound::IsStop() const {
    return ma_sound_is_playing(&sound_);
}

void Sound::SetLoop(bool enable) {
    ma_sound_set_looping(&sound_, enable);
}

bool Sound::IsLooping() const {
    return ma_sound_is_looping(&sound_);
}


void SoundFactory::Init() { }

void SoundFactory::Quit() {
    soundMap_.clear();
}

Sound* SoundFactory::Load(const std::string& filename, const std::string& name) {
    if (auto sound = Find(name); sound) {
        Logw("sound {} already loaded", name);
        return sound;
    } else {
        SoundID id = curID_++;
        auto s = std::make_unique<Sound>(id, filename, name);
        auto result = s.get();
        soundMap_[id] = std::move(s);
        return result;
    }
}

void SoundFactory::Remove(Sound* sound) {
    Remove(sound->ID());
}

void SoundFactory::Remove(SoundID id) {
    auto it = soundMap_.find(id);
    if (it != soundMap_.end()) {
        soundMap_.erase(it);
    }
}

void SoundFactory::Remove(const std::string& name) {
    auto sound = Find(name);
    if (!sound) return;
    Remove(sound->ID());
}

Sound* SoundFactory::Find(SoundID id) {
    auto it = soundMap_.find(id);
    if (it == soundMap_.end()) {
        return nullptr;
    } else {
        return it->second.get();
    }
}

Sound* SoundFactory::Find(const std::string& name) {
    for (auto& sound : soundMap_) {
        if (sound.second->Name() == name) {
            return sound.second.get();
        }
    }
    return nullptr;
}


SoundID SoundFactory::curID_ = 0;
std::unordered_map<SoundID, std::unique_ptr<Sound>> SoundFactory::soundMap_;

}