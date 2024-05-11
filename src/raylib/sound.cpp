#include "raylib/sound.h"
#include "raylib/raylibexception.h"

void raylib::Sound::set(const ::Sound& sound) {
    frameCount = sound.frameCount;
    stream     = sound.stream;
}

raylib::Sound::Sound() {
    stream     = {nullptr, nullptr, 0, 0, 0};
    frameCount = 0;
}

raylib::Sound::Sound(::AudioStream _stream, unsigned int _frameCount)
    : ::Sound{_stream, _frameCount} {}

raylib::Sound::Sound(Sound&& other) noexcept {
    set(other);

    other.stream     = {nullptr, nullptr, 0, 0, 0};
    other.frameCount = 0;
}

raylib::Sound::Sound(const std::string& fileName) {
    Load(fileName);
}

raylib::Sound::Sound(const ::Wave& wave) {
    Load(wave);
}

raylib::Sound::~Sound() {
    Unload();
}

raylib::Sound& raylib::Sound::operator=(Sound&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);
    other.frameCount = 0;
    other.stream     = {nullptr, nullptr, 0, 0, 0};

    return *this;
}

unsigned int raylib::Sound::GetFrameCount() const {
    return frameCount;
}

::AudioStream raylib::Sound::GetStream() const {
    return stream;
}

raylib::Sound& raylib::Sound::Update(const void* data, int samplesCount) {
    ::UpdateSound(*this, data, samplesCount);
    return *this;
}

raylib::Sound& raylib::Sound::Update(const void* data) {
    ::UpdateSound(*this, data, static_cast<int>(frameCount));
    return *this;
}

void raylib::Sound::Unload() {
    // Protect against calling UnloadSound() twice.
    if (frameCount != 0) {
        ::UnloadSound(*this);
        frameCount = 0;
    }
}

raylib::Sound& raylib::Sound::Play() {
    ::PlaySound(*this);
    return *this;
}

raylib::Sound& raylib::Sound::Stop() {
    ::StopSound(*this);
    return *this;
}

raylib::Sound& raylib::Sound::Pause() {
    ::PauseSound(*this);
    return *this;
}

raylib::Sound& raylib::Sound::Resume() {
    ::ResumeSound(*this);
    return *this;
}

bool raylib::Sound::IsPlaying() const {
    return ::IsSoundPlaying(*this);
}

raylib::Sound& raylib::Sound::SetVolume(float volume) {
    ::SetSoundVolume(*this, volume);
    return *this;
}

raylib::Sound& raylib::Sound::SetPitch(float pitch) {
    ::SetSoundPitch(*this, pitch);
    return *this;
}

raylib::Sound& raylib::Sound::SetPan(float pan) {
    ::SetSoundPan(*this, pan);
    return *this;
}

void raylib::Sound::Load(const std::string& fileName) {
    set(::LoadSound(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Sound from file");
    }
}

void raylib::Sound::Load(const ::Wave& wave) {
    set(::LoadSoundFromWave(wave));
    if (!IsReady()) {
        throw RaylibException("Failed to load Wave");
    }
}

bool raylib::Sound::IsReady() const {
    return ::IsSoundReady(*this);
}
