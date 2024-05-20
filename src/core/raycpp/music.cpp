#include "core/raycpp/music.h"
#include "core/raycpp/raylibexception.h"
#include <format>

core::raycpp::Music::Music(
    ::AudioStream _stream,
    unsigned int  _frameCount,
    bool          _looping,
    int           _ctxType,
    void*         _ctxData
)
    : ::Music{_stream, _frameCount, _looping, _ctxType, _ctxData} {}

core::raycpp::Music::Music(const ::Music& music) {
    set(music);
}

core::raycpp::Music::Music(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::Music::Music(
    const std::string& fileType,
    unsigned char*     data,
    int                dataSize
) {
    Load(fileType, data, dataSize);
}

core::raycpp::Music::Music(Music&& other) noexcept {
    set(other);

    other.stream     = {};
    other.frameCount = 0;
    other.looping    = false;
    other.ctxType    = 0;
    other.ctxData    = nullptr;
}

core::raycpp::Music::~Music() {
    Unload();
}

::AudioStream core::raycpp::Music::GetStream() const {
    return stream;
}

unsigned int core::raycpp::Music::GetFrameCount() const {
    return frameCount;
}

bool core::raycpp::Music::GetLooping() const {
    return looping;
}

void core::raycpp::Music::SetLooping(bool value) {
    looping = value;
}

int core::raycpp::Music::GetCtxType() const {
    return ctxType;
}

void* core::raycpp::Music::GetCtxData() const {
    return ctxData;
}

core::raycpp::Music& core::raycpp::Music::operator=(const ::Music& music) {
    set(music);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::operator=(Music&& other) noexcept {
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

void core::raycpp::Music::Unload() {
    ::UnloadMusicStream(*this);
}

core::raycpp::Music& core::raycpp::Music::Play() {
    ::PlayMusicStream(*this);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::Update() {
    ::UpdateMusicStream(*this);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::Stop() {
    ::StopMusicStream(*this);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::Pause() {
    ::PauseMusicStream(*this);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::Resume() {
    ::ResumeMusicStream(*this);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::Seek(float position) {
    SeekMusicStream(*this, position);
    return *this;
}

bool core::raycpp::Music::IsPlaying() const {
    return ::IsMusicStreamPlaying(*this);
}

core::raycpp::Music& core::raycpp::Music::SetVolume(float volume) {
    ::SetMusicVolume(*this, volume);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::SetPitch(float pitch) {
    ::SetMusicPitch(*this, pitch);
    return *this;
}

core::raycpp::Music& core::raycpp::Music::SetPan(float pan) {
    ::SetMusicPan(*this, pan);
    return *this;
}

float core::raycpp::Music::GetTimeLength() const {
    return ::GetMusicTimeLength(*this);
}

float core::raycpp::Music::GetTimePlayed() const {
    return ::GetMusicTimePlayed(*this);
}

void core::raycpp::Music::Load(const std::string& fileName) {
    set(::LoadMusicStream(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException(
            std::format("Failed to load Music from file: {}", fileName)
        );
    }
}

void core::raycpp::Music::Load(
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

bool core::raycpp::Music::IsReady() const {
    return ::IsMusicReady(*this);
}
