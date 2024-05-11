#include "raylib/wave.h"
#include "raylib/raylibexception.h"

raylib::Wave::Wave(const ::Wave& wave) {
    set(wave);
}

raylib::Wave::Wave(
    unsigned int _frameCount,
    unsigned int _sampleRate,
    unsigned int _sampleSize,
    unsigned int _channels,
    void*        _data
)
    : ::Wave{_frameCount, _sampleRate, _sampleSize, _channels, _data} {
    // Nothing.
}

raylib::Wave::Wave(const std::string& fileName) {
    Load(fileName);
}

raylib::Wave::Wave(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize
) {
    Load(fileType, fileData, dataSize);
}

raylib::Wave::Wave(const Wave& other) {
    set(other.Copy());
}

raylib::Wave::Wave(Wave&& other) noexcept {
    set(other);

    other.frameCount = 0;
    other.sampleRate = 0;
    other.sampleSize = 0;
    other.channels   = 0;
    other.data       = nullptr;
}

raylib::Wave::~Wave() {
    Unload();
}

unsigned int raylib::Wave::GetFrameCount() const {
    return frameCount;
}

unsigned int raylib::Wave::GetSampleRate() const {
    return sampleRate;
}

unsigned int raylib::Wave::GetSampleSize() const {
    return sampleSize;
}

unsigned int raylib::Wave::GetChannels() const {
    return channels;
}

void* raylib::Wave::GetData() const {
    return data;
}

raylib::Wave& raylib::Wave::operator=(const ::Wave& wave) {
    set(wave);
    return *this;
}

raylib::Wave& raylib::Wave::operator=(const Wave& other) {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other.Copy());

    return *this;
}

raylib::Wave& raylib::Wave::operator=(Wave&& other) noexcept {
    if (this != &other) {
        return *this;
    }

    Unload();
    set(other);

    other.frameCount = 0;
    other.sampleRate = 0;
    other.sampleSize = 0;
    other.channels   = 0;
    other.data       = nullptr;

    return *this;
}

::Wave raylib::Wave::Copy() const {
    return ::WaveCopy(*this);
}

raylib::Wave& raylib::Wave::Crop(int initSample, int finalSample) {
    ::WaveCrop(this, initSample, finalSample);
    return *this;
}

raylib::Wave&
raylib::Wave::Format(int SampleRate, int SampleSize, int Channels) {
    ::WaveFormat(this, SampleRate, SampleSize, Channels);
    return *this;
}

float* raylib::Wave::LoadSamples() {
    return ::LoadWaveSamples(*this);
}

void raylib::Wave::UnloadSamples(float* samples) {
    ::UnloadWaveSamples(samples);
}

bool raylib::Wave::Export(const std::string& fileName) {
    // TODO(RobLoach): Throw exception on error.
    return ::ExportWave(*this, fileName.c_str());
}

bool raylib::Wave::ExportAsCode(const std::string& fileName) {
    // TODO(RobLoach): Throw exception on error.
    return ::ExportWaveAsCode(*this, fileName.c_str());
}

void raylib::Wave::Unload() {
    // Protect against calling UnloadWave() twice.
    if (data != nullptr) {
        ::UnloadWave(*this);
        data = nullptr;
    }
}

::Sound raylib::Wave::LoadSound() {
    return ::LoadSoundFromWave(*this);
}

raylib::Wave::operator ::Sound() {
    return LoadSound();
}

void raylib::Wave::Load(const std::string& fileName) {
    set(::LoadWave(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Wave from file: " + fileName);
    }
}

void raylib::Wave::Load(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize
) {
    set(::LoadWaveFromMemory(fileType.c_str(), fileData, dataSize));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Wave from file data of type: " + fileType
        );
    }
}

bool raylib::Wave::IsReady() const {
    return ::IsWaveReady(*this);
}

void raylib::Wave::set(const ::Wave& wave) {
    frameCount = wave.frameCount;
    sampleRate = wave.sampleRate;
    sampleSize = wave.sampleSize;
    channels   = wave.channels;
    data       = wave.data;
}
