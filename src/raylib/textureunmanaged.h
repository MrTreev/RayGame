#pragma once

#include "raylib/image.h"
#include "raylib/raylib.h"
#include "raylib/vector2.h"
#include <string>

namespace raylib {
class TextureUnmanaged: public ::Texture {
    static constexpr ::Color white = {255, 255, 255, 255};

public:
    TextureUnmanaged();
    TextureUnmanaged(
        unsigned int _id,
        int          _width,
        int          _height,
        int          _mipmaps = 1,
        int          _format  = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    );
    TextureUnmanaged(const ::Image& image, int layout);
    explicit TextureUnmanaged(const ::Texture& texture);
    explicit TextureUnmanaged(const ::Image& image);
    explicit TextureUnmanaged(const std::string& fileName);
    explicit TextureUnmanaged(::Texture&& other);

    unsigned int GetId() const;
    int          GetWidth() const;
    int          GetHeight() const;
    int          GetMipmaps() const;
    int          GetFormat() const;
    ::Vector2    GetSize() const;
    void         Load(const ::Image& image);
    void         Load(const ::Image& image, int layoutType);
    void         Load(const std::string& fileName);
    void         Unload();
    ::Image      GetData() const;
    explicit     operator Image() const;
    bool         IsReady() const;

    TextureUnmanaged& operator=(const ::Texture& texture);
    TextureUnmanaged& Update(const void* pixels);
    TextureUnmanaged& Update(::Rectangle rec, const void* pixels);
    TextureUnmanaged& GenMipmaps();
    TextureUnmanaged& SetFilter(int filterMode);
    TextureUnmanaged& SetWrap(int wrapMode);
    TextureUnmanaged&
    SetMaterial(::Material* material, int mapType = MATERIAL_MAP_NORMAL);
    TextureUnmanaged&
    SetMaterial(const ::Material& material, int mapType = MATERIAL_MAP_NORMAL);
    TextureUnmanaged& SetShapes(const ::Rectangle& source);
    TextureUnmanaged& SetShaderValue(const ::Shader& shader, int locIndex);

    void Draw(int posX = 0, int posY = 0, ::Color tint = white) const;
    void Draw(::Vector2 position, ::Color tint = white) const;
    void Draw(
        ::Vector2 position,
        float     rotation,
        float     scale = 1.0F,
        ::Color   tint  = white
    ) const;
    void Draw(
        ::Rectangle sourceRec,
        ::Vector2   position = {0, 0},
        ::Color     tint     = white
    ) const;
    void Draw(
        ::Rectangle sourceRec,
        ::Rectangle destRec,
        ::Vector2   origin   = {0, 0},
        float       rotation = 0,
        ::Color     tint     = white
    ) const;
    void Draw(
        ::NPatchInfo nPatchInfo,
        ::Rectangle  destRec,
        ::Vector2    origin   = {0, 0},
        float        rotation = 0,
        ::Color      tint     = white
    ) const;
    void DrawBillboard(
        const ::Camera& camera,
        ::Vector3       position,
        float           size,
        ::Color         tint = white
    ) const;
    void DrawBillboard(
        const ::Camera& camera,
        ::Rectangle     source,
        ::Vector3       position,
        ::Vector2       size,
        ::Color         tint = white
    ) const;
    void DrawBillboard(
        const ::Camera& camera,
        ::Rectangle     source,
        Vector3         position,
        ::Vector3       upv,
        Vector2         size,
        Vector2         origin,
        float           rotation = 0.0F,
        ::Color         tint     = white
    ) const;

protected:
    void set(const ::Texture& texture);
};

} // namespace raylib
