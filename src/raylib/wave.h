#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Wave: public ::Wave {
public:
    explicit Wave(const ::Wave& wave);
    explicit Wave(
        unsigned int _frameCount = 0,
        unsigned int _sampleRate = 0,
        unsigned int _sampleSize = 0,
        unsigned int _channels   = 0,
        void*        _data       = nullptr
    );
    explicit Wave(const std::string& fileName);
    Wave(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize
    );
    Wave(const Wave& other);
    Wave(Wave&& other) noexcept;
    ~Wave();

    unsigned int GetFrameCount() const;
    unsigned int GetSampleRate() const;
    unsigned int GetSampleSize() const;
    unsigned int GetChannels() const;
    void*        GetData() const;

    Wave& operator=(const ::Wave& wave);
    Wave& operator=(const Wave& other);
    Wave& operator=(Wave&& other) noexcept;

    Wave& Crop(int initSample, int finalSample);
    Wave& Format(int SampleRate, int SampleSize, int Channels = 2);

    ::Wave  Copy() const;
    float*  LoadSamples();
    ::Sound LoadSound();

    bool Export(const std::string& fileName);
    bool ExportAsCode(const std::string& fileName);

    void Unload();
    void Load(const std::string& fileName);
    void Load(
        const std::string&   fileType,
        const unsigned char* fileData,
        int                  dataSize
    );

    bool        IsReady() const;
    static void UnloadSamples(float* samples);
    explicit    operator ::Sound();

protected:
    void set(const ::Wave& wave);
};
} // namespace raylib
