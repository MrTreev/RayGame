#include "core/raycpp/wave.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::Wave::Wave(const ::Wave& wave) {
    set(wave);
}

core::raycpp::Wave::Wave(
    unsigned int _frameCount,
    unsigned int _sampleRate,
    unsigned int _sampleSize,
    unsigned int _channels,
    void*        _data
)
    : ::Wave{_frameCount, _sampleRate, _sampleSize, _channels, _data} {
    // Nothing.
}

core::raycpp::Wave::Wave(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::Wave::Wave(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize
) {
    Load(fileType, fileData, dataSize);
}

core::raycpp::Wave::Wave(const Wave& other) {
    set(other.Copy());
}

core::raycpp::Wave::Wave(Wave&& other) noexcept {
    set(other);

    other.frameCount = 0;
    other.sampleRate = 0;
    other.sampleSize = 0;
    other.channels   = 0;
    other.data       = nullptr;
}

core::raycpp::Wave::~Wave() {
    Unload();
}

unsigned int core::raycpp::Wave::GetFrameCount() const {
    return frameCount;
}

unsigned int core::raycpp::Wave::GetSampleRate() const {
    return sampleRate;
}

unsigned int core::raycpp::Wave::GetSampleSize() const {
    return sampleSize;
}

unsigned int core::raycpp::Wave::GetChannels() const {
    return channels;
}

void* core::raycpp::Wave::GetData() const {
    return data;
}

core::raycpp::Wave& core::raycpp::Wave::operator=(const ::Wave& wave) {
    set(wave);
    return *this;
}

core::raycpp::Wave& core::raycpp::Wave::operator=(const Wave& other) {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other.Copy());

    return *this;
}

core::raycpp::Wave& core::raycpp::Wave::operator=(Wave&& other) noexcept {
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

::Wave core::raycpp::Wave::Copy() const {
    return ::WaveCopy(*this);
}

core::raycpp::Wave& core::raycpp::Wave::Crop(int initSample, int finalSample) {
    ::WaveCrop(this, initSample, finalSample);
    return *this;
}

core::raycpp::Wave&
core::raycpp::Wave::Format(int SampleRate, int SampleSize, int Channels) {
    ::WaveFormat(this, SampleRate, SampleSize, Channels);
    return *this;
}

float* core::raycpp::Wave::LoadSamples() {
    return ::LoadWaveSamples(*this);
}

void core::raycpp::Wave::UnloadSamples(float* samples) {
    ::UnloadWaveSamples(samples);
}

bool core::raycpp::Wave::Export(const std::string& fileName) {
    // TODO(RobLoach): Throw exception on error.
    return ::ExportWave(*this, fileName.c_str());
}

bool core::raycpp::Wave::ExportAsCode(const std::string& fileName) {
    // TODO(RobLoach): Throw exception on error.
    return ::ExportWaveAsCode(*this, fileName.c_str());
}

void core::raycpp::Wave::Unload() {
    // Protect against calling UnloadWave() twice.
    if (data != nullptr) {
        ::UnloadWave(*this);
        data = nullptr;
    }
}

::Sound core::raycpp::Wave::LoadSound() {
    return ::LoadSoundFromWave(*this);
}

core::raycpp::Wave::operator ::Sound() {
    return LoadSound();
}

void core::raycpp::Wave::Load(const std::string& fileName) {
    set(::LoadWave(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Wave from file: " + fileName);
    }
}

void core::raycpp::Wave::Load(
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

bool core::raycpp::Wave::IsReady() const {
    return ::IsWaveReady(*this);
}

void core::raycpp::Wave::set(const ::Wave& wave) {
    frameCount = wave.frameCount;
    sampleRate = wave.sampleRate;
    sampleSize = wave.sampleSize;
    channels   = wave.channels;
    data       = wave.data;
}
