#include "raylib/music.h"
#include "raylib/raylibexception.h"
#include <format>

raylib::Music::Music(
    ::AudioStream _stream,
    unsigned int  _frameCount,
    bool          _looping,
    int           _ctxType,
    void*         _ctxData
)
    : ::Music{_stream, _frameCount, _looping, _ctxType, _ctxData} {}

raylib::Music::Music(const ::Music& music) {
    set(music);
}

raylib::Music::Music(const std::string& fileName) {
    Load(fileName);
}

raylib::Music::Music(
    const std::string& fileType,
    unsigned char*     data,
    int                dataSize
) {
    Load(fileType, data, dataSize);
}

raylib::Music::Music(Music&& other) noexcept {
    set(other);

    other.stream     = {};
    other.frameCount = 0;
    other.looping    = false;
    other.ctxType    = 0;
    other.ctxData    = nullptr;
}

raylib::Music::~Music() {
    Unload();
}

::AudioStream raylib::Music::GetStream() const {
    return stream;
}

unsigned int raylib::Music::GetFrameCount() const {
    return frameCount;
}

bool raylib::Music::GetLooping() const {
    return looping;
}

void raylib::Music::SetLooping(bool value) {
    looping = value;
}

int raylib::Music::GetCtxType() const {
    return ctxType;
}

void* raylib::Music::GetCtxData() const {
    return ctxData;
}

raylib::Music& raylib::Music::operator=(const ::Music& music) {
    set(music);
    return *this;
}

raylib::Music& raylib::Music::operator=(Music&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.ctxType    = 0;
    other.ctxData    = nullptr;
    other.looping    = false;
    other.frameCount = 0;
    other.stream     = {};

    return *this;
}

void raylib::Music::Unload() {
    ::UnloadMusicStream(*this);
}

raylib::Music& raylib::Music::Play() {
    ::PlayMusicStream(*this);
    return *this;
}

raylib::Music& raylib::Music::Update() {
    ::UpdateMusicStream(*this);
    return *this;
}

raylib::Music& raylib::Music::Stop() {
    ::StopMusicStream(*this);
    return *this;
}

raylib::Music& raylib::Music::Pause() {
    ::PauseMusicStream(*this);
    return *this;
}

raylib::Music& raylib::Music::Resume() {
    ::ResumeMusicStream(*this);
    return *this;
}

raylib::Music& raylib::Music::Seek(float position) {
    SeekMusicStream(*this, position);
    return *this;
}

bool raylib::Music::IsPlaying() const {
    return ::IsMusicStreamPlaying(*this);
}

raylib::Music& raylib::Music::SetVolume(float volume) {
    ::SetMusicVolume(*this, volume);
    return *this;
}

raylib::Music& raylib::Music::SetPitch(float pitch) {
    ::SetMusicPitch(*this, pitch);
    return *this;
}

raylib::Music& raylib::Music::SetPan(float pan) {
    ::SetMusicPan(*this, pan);
    return *this;
}

float raylib::Music::GetTimeLength() const {
    return ::GetMusicTimeLength(*this);
}

float raylib::Music::GetTimePlayed() const {
    return ::GetMusicTimePlayed(*this);
}

void raylib::Music::Load(const std::string& fileName) {
    set(::LoadMusicStream(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException(
            std::format("Failed to load Music from file: {}", fileName)
        );
    }
}

void raylib::Music::Load(
    const std::string& fileType,
    unsigned char*     data,
    int                dataSize
) {
    set(::LoadMusicStreamFromMemory(fileType.c_str(), data, dataSize));
    if (!IsReady()) {
        throw RaylibException(
            std::format("Failed to load Music from {} file dat", fileType)
        );
    }
}

bool raylib::Music::IsReady() const {
    return ::IsMusicReady(*this);
}
