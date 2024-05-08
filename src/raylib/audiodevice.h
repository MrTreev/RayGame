#pragma once

namespace raylib {
class AudioDevice {
public:
    explicit AudioDevice(bool lateInit = false);
    AudioDevice(const AudioDevice&)            = delete;
    AudioDevice(AudioDevice&&)                 = delete;
    AudioDevice& operator=(const AudioDevice&) = delete;
    AudioDevice& operator=(AudioDevice&&)      = delete;
    ~AudioDevice();
    static void Init();
    static void Close();
    static void SetVolume(float volume);
    static bool IsReady();
};
} // namespace raylib
