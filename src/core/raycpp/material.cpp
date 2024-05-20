#include "core/raycpp/material.h"

void core::raycpp::Material::set(const ::Material& material) {
    shader    = material.shader;
    maps      = material.maps;
    params[0] = material.params[0];
    params[1] = material.params[1];
    params[2] = material.params[2];
    params[3] = material.params[3];
}

core::raycpp::Material::Material(const ::Material& material) {
    set(material);
}

core::raycpp::Material::Material() {
    set(LoadMaterialDefault());
}

core::raycpp::Material::Material(Material&& other) noexcept {
    set(other);

    other.maps      = nullptr;
    other.shader    = {};
    other.params[0] = 0.0F;
    other.params[1] = 0.0F;
    other.params[2] = 0.0F;
    other.params[3] = 0.0F;
}

core::raycpp::Material::~Material() {
    Unload();
}

std::vector<core::raycpp::Material> core::raycpp::Material::Load(const std::string& fileName
) {
    int         count     = 0;
    // TODO(RobLoach): Material::Load() possibly leaks the materials array.
    ::Material* materials = ::LoadMaterials(fileName.c_str(), &count);
    return {materials, materials + count};
}

::Shader core::raycpp::Material::GetShader() const {
    return shader;
}

void core::raycpp::Material::SetShader(::Shader value) {
    shader = value;
}

::MaterialMap* core::raycpp::Material::GetMaps() const {
    return maps;
}

void core::raycpp::Material::SetMaps(::MaterialMap* value) {
    maps = value;
}

// TODO(RobLoach): Resolve the Material params being a float[4].
// GETTERSETTER(float[4], Params, params)

core::raycpp::Material& core::raycpp::Material::operator=(const ::Material& material) {
    set(material);
    return *this;
}

core::raycpp::Material& core::raycpp::Material::operator=(Material&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    Unload();
    set(other);
    other.maps   = nullptr;
    other.shader = {};
    return *this;
}

void core::raycpp::Material::Unload() {
    if (maps != nullptr) {
        ::UnloadMaterial(*this);
        maps = nullptr;
    }
}

core::raycpp::Material&
core::raycpp::Material::SetTexture(int mapType, const ::Texture2D& texture) {
    ::SetMaterialTexture(this, mapType, texture);
    return *this;
}

void core::raycpp::Material::DrawMesh(const ::Mesh& mesh, ::Matrix transform) const {
    ::DrawMesh(mesh, *this, transform);
}

void core::raycpp::Material::DrawMesh(
    const ::Mesh& mesh,
    ::Matrix*     transforms,
    int           instances
) const {
    ::DrawMeshInstanced(mesh, *this, transforms, instances);
}

bool core::raycpp::Material::IsReady() const {
    return ::IsMaterialReady(*this);
}
