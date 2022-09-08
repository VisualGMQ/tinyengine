#pragma once

#include "miniaudio/miniaudio.h"
#include "engine/core/vmath.hpp"

namespace engine {

using SoundID = unsigned int;

class Sound {
public:
    static void Init();
    static void Quit();
    static void PlaySound(const std::string& filename);

    Sound(SoundID id, const std::string& filename, const std::string& name, bool async = false, bool is3D = false);
    ~Sound();
    void Play();
    void Stop();
    void SetPosition(const Vec3& position);
    void SetDirection(const Vec3& dir);
    void SetVelocity(const Vec3& vel);
    void FadeIn(int milliseconds);
    void FadeOut(int milliseconds);
    bool IsStop() const;
    void SetLoop(bool);
    bool IsLooping() const;
    const std::string& Name() const { return name_; }
    SoundID ID() const { return id_; }

private:
    static ma_engine engine_;

    std::string name_;
    ma_sound sound_;
    SoundID id_;
};

class SoundFactory final {
public:
    SoundFactory() = delete;

    static void Init();
    static void Quit();

    static Sound* Load(const std::string& filename, const std::string& name);
    static void Remove(Sound*);
    static void Remove(SoundID);
    static void Remove(const std::string& name);
    static Sound* Find(SoundID);
    static Sound* Find(const std::string& name);

private:
    static SoundID curID_;
    static std::unordered_map<SoundID, std::unique_ptr<Sound>> soundMap_;
};

}