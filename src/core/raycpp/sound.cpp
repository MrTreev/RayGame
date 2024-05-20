#include "core/raycpp/sound.h"
#include "core/raycpp/raylibexception.h"

void core::raycpp::Sound::set(const ::Sound& sound) {
    frameCount = sound.frameCount;
    stream     = sound.stream;
}

core::raycpp::Sound::Sound() {
    stream     = {nullptr, nullptr, 0, 0, 0};
    frameCount = 0;
}

core::raycpp::Sound::Sound(::AudioStream _stream, unsigned int _frameCount)
    : ::Sound{_stream, _frameCount} {}

core::raycpp::Sound::Sound(Sound&& other) noexcept {
    set(other);

    other.stream     = {nullptr, nullptr, 0, 0, 0};
    other.frameCount = 0;
}

core::raycpp::Sound::Sound(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::Sound::Sound(const ::Wave& wave) {
    Load(wave);
}

core::raycpp::Sound::~Sound() {
    Unload();
}

core::raycpp::Sound& core::raycpp::Sound::operator=(Sound&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);
    other.frameCount = 0;
    other.stream     = {nullptr, nullptr, 0, 0, 0};

    return *this;
}

unsigned int core::raycpp::Sound::GetFrameCount() const {
    return frameCount;
}

::AudioStream core::raycpp::Sound::GetStream() const {
    return stream;
}

core::raycpp::Sound& core::raycpp::Sound::Update(const void* data, int samplesCount) {
    ::UpdateSound(*this, data, samplesCount);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::Update(const void* data) {
    ::UpdateSound(*this, data, static_cast<int>(frameCount));
    return *this;
}

void core::raycpp::Sound::Unload() {
    // Protect against calling UnloadSound() twice.
    if (frameCount != 0) {
        ::UnloadSound(*this);
        frameCount = 0;
    }
}

core::raycpp::Sound& core::raycpp::Sound::Play() {
    ::PlaySound(*this);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::Stop() {
    ::StopSound(*this);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::Pause() {
    ::PauseSound(*this);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::Resume() {
    ::ResumeSound(*this);
    return *this;
}

bool core::raycpp::Sound::IsPlaying() const {
    return ::IsSoundPlaying(*this);
}

core::raycpp::Sound& core::raycpp::Sound::SetVolume(float volume) {
    ::SetSoundVolume(*this, volume);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::SetPitch(float pitch) {
    ::SetSoundPitch(*this, pitch);
    return *this;
}

core::raycpp::Sound& core::raycpp::Sound::SetPan(float pan) {
    ::SetSoundPan(*this, pan);
    return *this;
}

void core::raycpp::Sound::Load(const std::string& fileName) {
    set(::LoadSound(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Sound from file");
    }
}

void core::raycpp::Sound::Load(const ::Wave& wave) {
    set(::LoadSoundFromWave(wave));
    if (!IsReady()) {
        throw RaylibException("Failed to load Wave");
    }
}

bool core::raycpp::Sound::IsReady() const {
    return ::IsSoundReady(*this);
}
