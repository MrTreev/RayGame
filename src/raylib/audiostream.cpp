#include "raylib/audiostream.h"
#include "raylib/raylibexception.h"

void raylib::AudioStream::set(const ::AudioStream& stream) {
    buffer     = stream.buffer;
    processor  = stream.processor;
    sampleRate = stream.sampleRate;
    sampleSize = stream.sampleSize;
    channels   = stream.channels;
}

raylib::AudioStream::AudioStream(const ::AudioStream& music) {
    set(music);
}

raylib::AudioStream::AudioStream(
    rAudioBuffer*    _buffer,
    rAudioProcessor* _processor,
    unsigned int     _sampleRate,
    unsigned int     _sampleSize,
    unsigned int     _channels
)
    : ::AudioStream{_buffer, _processor, _sampleRate, _sampleSize, _channels} {}

raylib::AudioStream::AudioStream(
    unsigned int _sampleRate,
    unsigned int _sampleSize,
    unsigned int _channels
) {
    Load(_sampleRate, _sampleSize, _channels);
}

raylib::AudioStream::~AudioStream() {
    Unload();
}

void raylib::AudioStream::Update(const void* data, int samplesCount) {
    ::UpdateAudioStream(*this, data, samplesCount);
}

void raylib::AudioStream::Unload() {
    if (IsReady()) {
        ::UnloadAudioStream(*this);
    }
}

bool raylib::AudioStream::IsProcessed() const {
    return ::IsAudioStreamProcessed(*this);
}

void raylib::AudioStream::Play() {
    ::PlayAudioStream(*this);
}

void raylib::AudioStream::Pause() {
    ::PauseAudioStream(*this);
}

void raylib::AudioStream::Resume() {
    ::ResumeAudioStream(*this);
}

bool raylib::AudioStream::IsPlaying() const {
    return ::IsAudioStreamPlaying(*this);
}

void raylib::AudioStream::Stop() {
    ::StopAudioStream(*this);
}

void raylib::AudioStream::SetVolume(float volume) {
    ::SetAudioStreamVolume(*this, volume);
}

void raylib::AudioStream::SetPitch(float pitch) {
    ::SetAudioStreamPitch(*this, pitch);
}

void raylib::AudioStream::SetPan(float pan) {
    ::SetAudioStreamPan(*this, pan);
}

void raylib::AudioStream::SetBufferSizeDefault(int size) {
    ::SetAudioStreamBufferSizeDefault(size);
}

void raylib::AudioStream::SetCallback(::AudioCallback callback) {
    ::SetAudioStreamCallback(*this, callback);
}

void raylib::AudioStream::AttachProcessor(::AudioCallback _processor) {
    ::AttachAudioStreamProcessor(*this, _processor);
}

void raylib::AudioStream::DetachProcessor(::AudioCallback _processor) {
    ::DetachAudioStreamProcessor(*this, _processor);
}

bool raylib::AudioStream::IsReady() const {
    return ::IsAudioStreamReady(*this);
}

void raylib::AudioStream::Load(
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

rAudioBuffer* raylib::AudioStream::GetBuffer() const {
    return buffer;
}

rAudioProcessor* raylib::AudioStream::GetProcessor() const {
    return processor;
}

unsigned int raylib::AudioStream::GetSampleRate() const {
    return sampleRate;
}

unsigned int raylib::AudioStream::GetSampleSize() const {
    return sampleSize;
}

unsigned int raylib::AudioStream::GetChannels() const {
    return channels;
}
