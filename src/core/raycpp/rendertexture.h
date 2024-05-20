#pragma once

#include "core/raycpp/raylib.h"
#include "core/raycpp/textureunmanaged.h"

namespace core::raycpp {
class RenderTexture: public ::RenderTexture {
public:
    RenderTexture();
    explicit RenderTexture(const ::RenderTexture& renderTexture);
    RenderTexture(
        unsigned int     _id,
        const ::Texture& _texture,
        const ::Texture& _depth
    );
    RenderTexture(int width, int height);
    RenderTexture(const RenderTexture&) = delete;
    RenderTexture(RenderTexture&& other) noexcept;
    ~RenderTexture();

    TextureUnmanaged GetTexture();
    TextureUnmanaged GetDepth();
    unsigned int     GetId() const;

    void SetTexture(const ::Texture& newTexture);
    void SetDepth(const ::Texture& newDepth);

    RenderTexture& operator=(const ::RenderTexture& _texture);
    RenderTexture& operator=(const RenderTexture&) = delete;
    RenderTexture& operator=(RenderTexture&& other) noexcept;

    void           Unload();
    RenderTexture& BeginMode();
    RenderTexture& EndMode();
    bool           IsReady() const;

    static RenderTexture Load(int width, int height);

protected:
    void set(const ::RenderTexture& renderTexture);
};

using RenderTexture2D = RenderTexture;

} // namespace core::raycpp
