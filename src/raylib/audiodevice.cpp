#include "raylib/audiodevice.h"
#include "raylib/raylib.h"
#include "raylib/raylibexception.h"

raylib::AudioDevice::AudioDevice(bool lateInit) {
    if (!lateInit) {
        Init();
    }
}

raylib::AudioDevice::~AudioDevice() {
    Close();
}

void raylib::AudioDevice::Init() {
    ::InitAudioDevice();
    if (!IsReady()) {
        throw raylib::RaylibException("Failed to initialize AudioDevice");
    }
}

void raylib::AudioDevice::Close() {
    ::CloseAudioDevice();
}

void raylib::AudioDevice::SetVolume(float volume) {
    ::SetMasterVolume(volume);
}

bool raylib::AudioDevice::IsReady() {
    return ::IsAudioDeviceReady();
}
