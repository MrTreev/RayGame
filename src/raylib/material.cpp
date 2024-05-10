#include "raylib/material.h"

void raylib::Material::set(const ::Material& material) {
    shader    = material.shader;
    maps      = material.maps;
    params[0] = material.params[0];
    params[1] = material.params[1];
    params[2] = material.params[2];
    params[3] = material.params[3];
}

raylib::Material::Material(const ::Material& material) {
    set(material);
}

raylib::Material::Material() {
    set(LoadMaterialDefault());
}

raylib::Material::Material(Material&& other) noexcept {
    set(other);

    other.maps      = nullptr;
    other.shader    = {};
    other.params[0] = 0.0F;
    other.params[1] = 0.0F;
    other.params[2] = 0.0F;
    other.params[3] = 0.0F;
}

raylib::Material::~Material() {
    Unload();
}

std::vector<raylib::Material> raylib::Material::Load(const std::string& fileName
) {
    int         count     = 0;
    // TODO(RobLoach): Material::Load() possibly leaks the materials array.
    ::Material* materials = ::LoadMaterials(fileName.c_str(), &count);
    return {materials, materials + count};
}

::Shader raylib::Material::GetShader() const {
    return shader;
}

void raylib::Material::SetShader(::Shader value) {
    shader = value;
}

::MaterialMap* raylib::Material::GetMaps() const {
    return maps;
}

void raylib::Material::SetMaps(::MaterialMap* value) {
    maps = value;
}

// TODO(RobLoach): Resolve the Material params being a float[4].
// GETTERSETTER(float[4], Params, params)

raylib::Material& raylib::Material::operator=(const ::Material& material) {
    set(material);
    return *this;
}

raylib::Material& raylib::Material::operator=(Material&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    Unload();
    set(other);
    other.maps   = nullptr;
    other.shader = {};
    return *this;
}

void raylib::Material::Unload() {
    if (maps != nullptr) {
        ::UnloadMaterial(*this);
        maps = nullptr;
    }
}

raylib::Material&
raylib::Material::SetTexture(int mapType, const ::Texture2D& texture) {
    ::SetMaterialTexture(this, mapType, texture);
    return *this;
}

void raylib::Material::DrawMesh(const ::Mesh& mesh, ::Matrix transform) const {
    ::DrawMesh(mesh, *this, transform);
}

void raylib::Material::DrawMesh(
    const ::Mesh& mesh,
    ::Matrix*     transforms,
    int           instances
) const {
    ::DrawMeshInstanced(mesh, *this, transforms, instances);
}

bool raylib::Material::IsReady() const {
    return ::IsMaterialReady(*this);
}
