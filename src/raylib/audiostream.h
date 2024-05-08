#pragma once

#include "raylib/raylib.h"

namespace raylib {

class AudioStream: public ::AudioStream {
public:
    explicit AudioStream(const ::AudioStream& music);

    explicit AudioStream(
        rAudioBuffer*    _buffer     = nullptr,
        rAudioProcessor* _processor  = nullptr,
        unsigned int     _sampleRate = 0,
        unsigned int     _sampleSize = 0,
        unsigned int     _channels   = 0
    );

    AudioStream(
        unsigned int _sampleRate,
        unsigned int _sampleSize,
        unsigned int _channels = 2
    );

    AudioStream(const AudioStream&)                  = delete;
    AudioStream(AudioStream&& other)                 = delete;
    AudioStream& operator=(AudioStream&& other)      = delete;
    AudioStream& operator=(const AudioStream& other) = delete;
    ~AudioStream();

    void Unload();
    void Update(const void* data, int samplesCount);
    void Play();
    void Pause();
    void Resume();
    void Stop();
    void SetVolume(float volume = 1.0F);
    void SetPitch(float pitch);
    void SetPan(float pan = 0.5F);
    void SetCallback(::AudioCallback callback);
    void AttachProcessor(::AudioCallback _processor);
    void DetachProcessor(::AudioCallback _processor);

    void Load(
        unsigned int SampleRate,
        unsigned int SampleSize,
        unsigned int Channels = 2
    );

    static void SetBufferSizeDefault(int size);

    bool             IsPlaying() const;
    bool             IsProcessed() const;
    bool             IsReady() const;
    rAudioBuffer*    GetBuffer() const;
    rAudioProcessor* GetProcessor() const;
    unsigned int     GetSampleRate() const;
    unsigned int     GetSampleSize() const;
    unsigned int     GetChannels() const;

protected:
    void set(const ::AudioStream& stream);
};

} // namespace raylib
