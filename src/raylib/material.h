#pragma once

#include "raylib/raylib.h"
#include <string>
#include <vector>

namespace raylib {
class Material: public ::Material {
public:
    explicit Material(const ::Material& material);
    Material();
    Material(const Material&) = delete;
    Material(Material&& other) noexcept;
    ~Material();
    static std::vector<Material> Load(const std::string& fileName);

    ::Shader       GetShader() const;
    Material&      operator=(const Material&) = delete;
    Material&      operator=(Material&& other) noexcept;
    void           SetShader(::Shader value);
    ::MaterialMap* GetMaps() const;
    void           SetMaps(::MaterialMap* value);
    // TODO(RobLoach): Resolve the Material params being a float[4].
    // GETTERSETTER(float[4], Params, params)

    Material& operator=(const ::Material& material);
    Material& SetTexture(int mapType, const ::Texture2D& texture);
    void      Unload();
    void      DrawMesh(const ::Mesh& mesh, ::Matrix transform) const;
    void
    DrawMesh(const ::Mesh& mesh, ::Matrix* transforms, int instances) const;
    bool IsReady() const;

protected:
    void set(const ::Material& material);
};
} // namespace raylib
