#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Sound: public ::Sound {
public:
    explicit Sound(const std::string& fileName);
    Sound(::AudioStream _stream, unsigned int _frameCount);
    Sound();
    Sound(const Sound&)            = delete;
    Sound& operator=(const Sound&) = delete;
    Sound(Sound&& other) noexcept;
    Sound& operator=(Sound&& other) noexcept;
    explicit Sound(const ::Wave& wave);
    ~Sound();

    unsigned int  GetFrameCount() const;
    ::AudioStream GetStream() const;
    Sound&        Update(const void* data, int samplesCount);
    Sound&        Update(const void* data);
    void          Unload();
    Sound&        Play();
    Sound&        Stop();
    Sound&        Pause();
    Sound&        Resume();
    bool          IsPlaying() const;
    Sound&        SetVolume(float volume);
    Sound&        SetPitch(float pitch);
    Sound&        SetPan(float pan = 0.5F);
    void          Load(const std::string& fileName);
    void          Load(const ::Wave& wave);
    bool          IsReady() const;

protected:
    void set(const ::Sound& sound);
};
} // namespace raylib
