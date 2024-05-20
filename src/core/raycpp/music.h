#pragma once

#include "core/raycpp/raylib.h"
#include <string>

namespace core::raycpp {
class Music: public ::Music {
public:
    explicit Music(
        ::AudioStream _stream     = {nullptr, nullptr, 0, 0, 0},
        unsigned int  _frameCount = 0,
        bool          _looping    = false,
        int           _ctxType    = 0,
        void*         _ctxData    = nullptr
    );
    explicit Music(const ::Music& music);
    explicit Music(const std::string& fileName);
    Music(const std::string& fileType, unsigned char* data, int dataSize);
    Music(Music&& other) noexcept;
    Music& operator=(const Music&) = delete;
    Music(const Music&)            = delete;
    ~Music();

    Music& operator=(const ::Music& music);
    Music& operator=(Music&& other) noexcept;

    Music& Play();
    Music& Update();
    Music& Stop();
    Music& Pause();
    Music& Resume();
    Music& Seek(float position);
    Music& SetVolume(float volume);
    Music& SetPitch(float pitch);
    Music& SetPan(float pan = 0.5F);

    ::AudioStream GetStream() const;
    unsigned int  GetFrameCount() const;
    bool          GetLooping() const;
    int           GetCtxType() const;
    void*         GetCtxData() const;
    bool          IsPlaying() const;
    float         GetTimeLength() const;
    float         GetTimePlayed() const;
    bool          IsReady() const;

    void Load(const std::string& fileName);
    void Load(const std::string& fileType, unsigned char* data, int dataSize);
    void Unload();
    void SetLooping(bool value);

protected:
    void set(const ::Music& music) {
        stream     = music.stream;
        frameCount = music.frameCount;
        looping    = music.looping;
        ctxType    = music.ctxType;
        ctxData    = music.ctxData;
    }
};
} // namespace core::raycpp
