#include "core/raycpp/audiostream.h"
#include "core/raycpp/raylibexception.h"

void core::raycpp::AudioStream::set(const ::AudioStream& stream) {
    buffer     = stream.buffer;
    processor  = stream.processor;
    sampleRate = stream.sampleRate;
    sampleSize = stream.sampleSize;
    channels   = stream.channels;
}

core::raycpp::AudioStream::AudioStream(const ::AudioStream& music) {
    set(music);
}

core::raycpp::AudioStream::AudioStream(
    rAudioBuffer*    _buffer,
    rAudioProcessor* _processor,
    unsigned int     _sampleRate,
    unsigned int     _sampleSize,
    unsigned int     _channels
)
    : ::AudioStream{_buffer, _processor, _sampleRate, _sampleSize, _channels} {}

core::raycpp::AudioStream::AudioStream(
    unsigned int _sampleRate,
    unsigned int _sampleSize,
    unsigned int _channels
) {
    Load(_sampleRate, _sampleSize, _channels);
}

core::raycpp::AudioStream::~AudioStream() {
    Unload();
}

void core::raycpp::AudioStream::Update(const void* data, int samplesCount) {
    ::UpdateAudioStream(*this, data, samplesCount);
}

void core::raycpp::AudioStream::Unload() {
    if (IsReady()) {
        ::UnloadAudioStream(*this);
    }
}

bool core::raycpp::AudioStream::IsProcessed() const {
    return ::IsAudioStreamProcessed(*this);
}

void core::raycpp::AudioStream::Play() {
    ::PlayAudioStream(*this);
}

void core::raycpp::AudioStream::Pause() {
    ::PauseAudioStream(*this);
}

void core::raycpp::AudioStream::Resume() {
    ::ResumeAudioStream(*this);
}

bool core::raycpp::AudioStream::IsPlaying() const {
    return ::IsAudioStreamPlaying(*this);
}

void core::raycpp::AudioStream::Stop() {
    ::StopAudioStream(*this);
}

void core::raycpp::AudioStream::SetVolume(float volume) {
    ::SetAudioStreamVolume(*this, volume);
}

void core::raycpp::AudioStream::SetPitch(float pitch) {
    ::SetAudioStreamPitch(*this, pitch);
}

void core::raycpp::AudioStream::SetPan(float pan) {
    ::SetAudioStreamPan(*this, pan);
}

void core::raycpp::AudioStream::SetBufferSizeDefault(int size) {
    ::SetAudioStreamBufferSizeDefault(size);
}

void core::raycpp::AudioStream::SetCallback(::AudioCallback callback) {
    ::SetAudioStreamCallback(*this, callback);
}

void core::raycpp::AudioStream::AttachProcessor(::AudioCallback _processor) {
    ::AttachAudioStreamProcessor(*this, _processor);
}

void core::raycpp::AudioStream::DetachProcessor(::AudioCallback _processor) {
    ::DetachAudioStreamProcessor(*this, _processor);
}

bool core::raycpp::AudioStream::IsReady() const {
    return ::IsAudioStreamReady(*this);
}

void core::raycpp::AudioStream::Load(
    unsigned int SampleRate,
    unsigned int SampleSize,
    unsigned int Channels
) {
    Unload();
    set(::LoadAudioStream(SampleRate, SampleSize, Channels));
    if (!IsReady()) {
        throw RaylibException("Failed to load audio stream");
    }
}

rAudioBuffer* core::raycpp::AudioStream::GetBuffer() const {
    return buffer;
}

rAudioProcessor* core::raycpp::AudioStream::GetProcessor() const {
    return processor;
}

unsigned int core::raycpp::AudioStream::GetSampleRate() const {
    return sampleRate;
}

unsigned int core::raycpp::AudioStream::GetSampleSize() const {
    return sampleSize;
}

unsigned int core::raycpp::AudioStream::GetChannels() const {
    return channels;
}
