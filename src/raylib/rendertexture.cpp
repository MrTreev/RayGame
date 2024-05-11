#include "raylib/rendertexture.h"

raylib::RenderTexture::RenderTexture() {
    id = 0;
}

raylib::RenderTexture::RenderTexture(const ::RenderTexture& renderTexture) {
    set(renderTexture);
}

raylib::RenderTexture::RenderTexture(
    unsigned int     _id,
    const ::Texture& _texture,
    const ::Texture& _depth
)
    : ::RenderTexture{_id, _texture, _depth} {}

raylib::RenderTexture::RenderTexture(int width, int height) {
    set(::LoadRenderTexture(width, height));
}

raylib::RenderTexture::RenderTexture(RenderTexture&& other) noexcept {
    set(other);

    other.id      = 0;
    other.texture = {};
    other.depth   = {};
}

unsigned int raylib::RenderTexture::GetId() const {
    return id;
}

raylib::TextureUnmanaged raylib::RenderTexture::GetTexture() {
    return TextureUnmanaged(texture);
}

void raylib::RenderTexture::SetTexture(const ::Texture& newTexture) {
    texture = newTexture;
}

raylib::TextureUnmanaged raylib::RenderTexture::GetDepth() {
    return TextureUnmanaged(depth);
}

void raylib::RenderTexture::SetDepth(const ::Texture& newDepth) {
    depth = newDepth;
}

raylib::RenderTexture&
raylib::RenderTexture::operator=(const ::RenderTexture& _texture) {
    set(_texture);
    return *this;
}

raylib::RenderTexture& raylib::RenderTexture::operator=(RenderTexture&& other
) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.id      = 0;
    other.texture = {};
    other.depth   = {};

    return *this;
}

raylib::RenderTexture::~RenderTexture() {
    Unload();
}

void raylib::RenderTexture::Unload() {
    UnloadRenderTexture(*this);
}

raylib::RenderTexture& raylib::RenderTexture::BeginMode() {
    ::BeginTextureMode(*this);
    return *this;
}

raylib::RenderTexture& raylib::RenderTexture::EndMode() {
    ::EndTextureMode();
    return *this;
}

raylib::RenderTexture raylib::RenderTexture::Load(int width, int height) {
    return RenderTexture(::LoadRenderTexture(width, height));
}

bool raylib::RenderTexture::IsReady() const {
    return ::IsRenderTextureReady(*this);
}

void raylib::RenderTexture::set(const ::RenderTexture& renderTexture) {
    id      = renderTexture.id;
    texture = renderTexture.texture;
    depth   = renderTexture.depth;
}
