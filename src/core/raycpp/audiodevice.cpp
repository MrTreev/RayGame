#include "core/raycpp/audiodevice.h"
#include "core/raycpp/raylib.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::AudioDevice::AudioDevice(bool lateInit) {
    if (!lateInit) {
        Init();
    }
}

core::raycpp::AudioDevice::~AudioDevice() {
    Close();
}

void core::raycpp::AudioDevice::Init() {
    ::InitAudioDevice();
    if (!IsReady()) {
        throw core::raycpp::RaylibException("Failed to initialize AudioDevice");
    }
}

void core::raycpp::AudioDevice::Close() {
    ::CloseAudioDevice();
}

void core::raycpp::AudioDevice::SetVolume(float volume) {
    ::SetMasterVolume(volume);
}

bool core::raycpp::AudioDevice::IsReady() {
    return ::IsAudioDeviceReady();
}
