#include "raylib/shader.h"

void raylib::Shader::set(const ::Shader& shader) {
    id   = shader.id;
    locs = shader.locs;
}

raylib::Shader::Shader(const ::Shader& shader) {
    set(shader);
}

raylib::Shader::Shader(unsigned int _id, int* _locs)
    : ::Shader{_id, _locs} {}

raylib::Shader::Shader(
    const std::string& vsFileName,
    const std::string& fsFileName
) {
    set(::LoadShader(vsFileName.c_str(), fsFileName.c_str()));
}

raylib::Shader::Shader(const char* vsFileName, const char* fsFileName) {
    set(::LoadShader(vsFileName, fsFileName));
}

raylib::Shader::Shader(Shader&& other) noexcept {
    set(other);

    other.id   = 0;
    other.locs = nullptr;
}

::Shader raylib::Shader::Load(
    const std::string& vsFileName,
    const std::string& fsFileName
) {
    return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
}

::Shader raylib::Shader::Load(const char* vsFileName, const char* fsFileName) {
    return ::LoadShader(vsFileName, fsFileName);
}

::Shader raylib::Shader::LoadFromMemory(
    const std::string& vsCode,
    const std::string& fsCode
) {
    return ::LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
}

::Shader
raylib::Shader::LoadFromMemory(const char* vsCode, const char* fsCode) {
    return ::LoadShaderFromMemory(vsCode, fsCode);
}

unsigned int raylib::Shader::GetId() const {
    return id;
}

int* raylib::Shader::GetLocs() const {
    return locs;
}

raylib::Shader& raylib::Shader::operator=(const ::Shader& shader) {
    set(shader);
    return *this;
}

raylib::Shader& raylib::Shader::operator=(Shader&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.id   = 0;
    other.locs = nullptr;

    return *this;
}

raylib::Shader::~Shader() {
    Unload();
}

void raylib::Shader::Unload() {
    if (locs != nullptr) {
        ::UnloadShader(*this);
    }
}

raylib::Shader& raylib::Shader::BeginMode() {
    ::BeginShaderMode(*this);
    return *this;
}

raylib::Shader& raylib::Shader::EndMode() {
    ::EndShaderMode();
    return *this;
}

int raylib::Shader::GetLocation(const std::string& uniformName) const {
    return ::GetShaderLocation(*this, uniformName.c_str());
}

int raylib::Shader::GetLocationAttrib(const std::string& attribName) const {
    return ::GetShaderLocationAttrib(*this, attribName.c_str());
}

raylib::Shader&
raylib::Shader::SetValue(int uniformLoc, const void* value, int uniformType) {
    ::SetShaderValue(*this, uniformLoc, value, uniformType);
    return *this;
}

raylib::Shader& raylib::Shader::SetValue(
    int         uniformLoc,
    const void* value,
    int         uniformType,
    int         count
) {
    ::SetShaderValueV(*this, uniformLoc, value, uniformType, count);
    return *this;
}

raylib::Shader& raylib::Shader::SetValue(int uniformLoc, const ::Matrix& mat) {
    ::SetShaderValueMatrix(*this, uniformLoc, mat);
    return *this;
}

raylib::Shader&
raylib::Shader::SetValue(int uniformLoc, const ::Texture2D& texture) {
    ::SetShaderValueTexture(*this, uniformLoc, texture);
    return *this;
}

bool raylib::Shader::IsReady() const {
    return id != 0 && locs != nullptr;
}
