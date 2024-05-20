#include "core/raycpp/rendertexture.h"

core::raycpp::RenderTexture::RenderTexture() {
    id = 0;
}

core::raycpp::RenderTexture::RenderTexture(const ::RenderTexture& renderTexture) {
    set(renderTexture);
}

core::raycpp::RenderTexture::RenderTexture(
    unsigned int     _id,
    const ::Texture& _texture,
    const ::Texture& _depth
)
    : ::RenderTexture{_id, _texture, _depth} {}

core::raycpp::RenderTexture::RenderTexture(int width, int height) {
    set(::LoadRenderTexture(width, height));
}

core::raycpp::RenderTexture::RenderTexture(RenderTexture&& other) noexcept {
    set(other);

    other.id      = 0;
    other.texture = {};
    other.depth   = {};
}

unsigned int core::raycpp::RenderTexture::GetId() const {
    return id;
}

core::raycpp::TextureUnmanaged core::raycpp::RenderTexture::GetTexture() {
    return TextureUnmanaged(texture);
}

void core::raycpp::RenderTexture::SetTexture(const ::Texture& newTexture) {
    texture = newTexture;
}

core::raycpp::TextureUnmanaged core::raycpp::RenderTexture::GetDepth() {
    return TextureUnmanaged(depth);
}

void core::raycpp::RenderTexture::SetDepth(const ::Texture& newDepth) {
    depth = newDepth;
}

core::raycpp::RenderTexture&
core::raycpp::RenderTexture::operator=(const ::RenderTexture& _texture) {
    set(_texture);
    return *this;
}

core::raycpp::RenderTexture& core::raycpp::RenderTexture::operator=(RenderTexture&& other
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

core::raycpp::RenderTexture::~RenderTexture() {
    Unload();
}

void core::raycpp::RenderTexture::Unload() {
    UnloadRenderTexture(*this);
}

core::raycpp::RenderTexture& core::raycpp::RenderTexture::BeginMode() {
    ::BeginTextureMode(*this);
    return *this;
}

core::raycpp::RenderTexture& core::raycpp::RenderTexture::EndMode() {
    ::EndTextureMode();
    return *this;
}

core::raycpp::RenderTexture core::raycpp::RenderTexture::Load(int width, int height) {
    return RenderTexture(::LoadRenderTexture(width, height));
}

bool core::raycpp::RenderTexture::IsReady() const {
    return ::IsRenderTextureReady(*this);
}

void core::raycpp::RenderTexture::set(const ::RenderTexture& renderTexture) {
    id      = renderTexture.id;
    texture = renderTexture.texture;
    depth   = renderTexture.depth;
}
