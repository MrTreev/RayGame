#include "core/raycpp/shader.h"

void core::raycpp::Shader::set(const ::Shader& shader) {
    id   = shader.id;
    locs = shader.locs;
}

core::raycpp::Shader::Shader(const ::Shader& shader) {
    set(shader);
}

core::raycpp::Shader::Shader(unsigned int _id, int* _locs)
    : ::Shader{_id, _locs} {}

core::raycpp::Shader::Shader(
    const std::string& vsFileName,
    const std::string& fsFileName
) {
    set(::LoadShader(vsFileName.c_str(), fsFileName.c_str()));
}

core::raycpp::Shader::Shader(const char* vsFileName, const char* fsFileName) {
    set(::LoadShader(vsFileName, fsFileName));
}

core::raycpp::Shader::Shader(Shader&& other) noexcept {
    set(other);

    other.id   = 0;
    other.locs = nullptr;
}

::Shader core::raycpp::Shader::Load(
    const std::string& vsFileName,
    const std::string& fsFileName
) {
    return ::LoadShader(vsFileName.c_str(), fsFileName.c_str());
}

::Shader core::raycpp::Shader::Load(const char* vsFileName, const char* fsFileName) {
    return ::LoadShader(vsFileName, fsFileName);
}

::Shader core::raycpp::Shader::LoadFromMemory(
    const std::string& vsCode,
    const std::string& fsCode
) {
    return ::LoadShaderFromMemory(vsCode.c_str(), fsCode.c_str());
}

::Shader
core::raycpp::Shader::LoadFromMemory(const char* vsCode, const char* fsCode) {
    return ::LoadShaderFromMemory(vsCode, fsCode);
}

unsigned int core::raycpp::Shader::GetId() const {
    return id;
}

int* core::raycpp::Shader::GetLocs() const {
    return locs;
}

core::raycpp::Shader& core::raycpp::Shader::operator=(const ::Shader& shader) {
    set(shader);
    return *this;
}

core::raycpp::Shader& core::raycpp::Shader::operator=(Shader&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.id   = 0;
    other.locs = nullptr;

    return *this;
}

core::raycpp::Shader::~Shader() {
    Unload();
}

void core::raycpp::Shader::Unload() {
    if (locs != nullptr) {
        ::UnloadShader(*this);
    }
}

core::raycpp::Shader& core::raycpp::Shader::BeginMode() {
    ::BeginShaderMode(*this);
    return *this;
}

core::raycpp::Shader& core::raycpp::Shader::EndMode() {
    ::EndShaderMode();
    return *this;
}

int core::raycpp::Shader::GetLocation(const std::string& uniformName) const {
    return ::GetShaderLocation(*this, uniformName.c_str());
}

int core::raycpp::Shader::GetLocationAttrib(const std::string& attribName) const {
    return ::GetShaderLocationAttrib(*this, attribName.c_str());
}

core::raycpp::Shader&
core::raycpp::Shader::SetValue(int uniformLoc, const void* value, int uniformType) {
    ::SetShaderValue(*this, uniformLoc, value, uniformType);
    return *this;
}

core::raycpp::Shader& core::raycpp::Shader::SetValue(
    int         uniformLoc,
    const void* value,
    int         uniformType,
    int         count
) {
    ::SetShaderValueV(*this, uniformLoc, value, uniformType, count);
    return *this;
}

core::raycpp::Shader& core::raycpp::Shader::SetValue(int uniformLoc, const ::Matrix& mat) {
    ::SetShaderValueMatrix(*this, uniformLoc, mat);
    return *this;
}

core::raycpp::Shader&
core::raycpp::Shader::SetValue(int uniformLoc, const ::Texture2D& texture) {
    ::SetShaderValueTexture(*this, uniformLoc, texture);
    return *this;
}

bool core::raycpp::Shader::IsReady() const {
    return id != 0 && locs != nullptr;
}
