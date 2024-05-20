#include "core/raycpp/textureunmanaged.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::TextureUnmanaged::TextureUnmanaged()
    : ::Texture{0, 0, 0, 0, 0} {}

core::raycpp::TextureUnmanaged::TextureUnmanaged(
    unsigned int _id,
    int          _width,
    int          _height,
    int          _mipmaps,
    int          _format
)
    : ::Texture{_id, _width, _height, _mipmaps, _format} {}

core::raycpp::TextureUnmanaged::TextureUnmanaged(const ::Texture& texture)
    : ::Texture{
        texture.id,
        texture.width,
        texture.height,
        texture.mipmaps,
        texture.format
    } {}

core::raycpp::TextureUnmanaged::TextureUnmanaged(const ::Image& image) {
    Load(Image(image));
}

core::raycpp::TextureUnmanaged::TextureUnmanaged(const ::Image& image, int layout) {
    Load(image, layout);
}

core::raycpp::TextureUnmanaged::TextureUnmanaged(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::TextureUnmanaged::TextureUnmanaged(::Texture&& other)
    : ::Texture{
        other.id,
        other.width,
        other.height,
        other.mipmaps,
        other.format
    } {}

unsigned int core::raycpp::TextureUnmanaged::GetId() const {
    return id;
}

int core::raycpp::TextureUnmanaged::GetWidth() const {
    return width;
}

int core::raycpp::TextureUnmanaged::GetHeight() const {
    return height;
}

int core::raycpp::TextureUnmanaged::GetMipmaps() const {
    return mipmaps;
}

int core::raycpp::TextureUnmanaged::GetFormat() const {
    return format;
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::operator=(const ::Texture& texture) {
    set(texture);
    return *this;
}

::Vector2 core::raycpp::TextureUnmanaged::GetSize() const {
    return {static_cast<float>(width), static_cast<float>(height)};
}

void core::raycpp::TextureUnmanaged::Load(const ::Image& image) {
    set(::LoadTextureFromImage(image));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from Image");
    }
}

void core::raycpp::TextureUnmanaged::Load(const ::Image& image, int layoutType) {
    set(::LoadTextureCubemap(image, layoutType));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from Cubemap");
    }
}

void core::raycpp::TextureUnmanaged::Load(const std::string& fileName) {
    set(::LoadTexture(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from file: " + fileName);
    }
}

void core::raycpp::TextureUnmanaged::Unload() {
    // Protect against calling UnloadTexture() twice.
    if (id != 0) {
        ::UnloadTexture(*this);
        id = 0;
    }
}

core::raycpp::TextureUnmanaged& core::raycpp::TextureUnmanaged::Update(const void* pixels) {
    ::UpdateTexture(*this, pixels);
    return *this;
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::Update(::Rectangle rec, const void* pixels) {
    UpdateTextureRec(*this, rec, pixels);
    return *this;
}

::Image core::raycpp::TextureUnmanaged::GetData() const {
    return ::LoadImageFromTexture(*this);
}

core::raycpp::TextureUnmanaged::operator Image() const {
    return Image(GetData());
}

core::raycpp::TextureUnmanaged& core::raycpp::TextureUnmanaged::GenMipmaps() {
    ::GenTextureMipmaps(this);
    return *this;
}

core::raycpp::TextureUnmanaged& core::raycpp::TextureUnmanaged::SetFilter(int filterMode) {
    ::SetTextureFilter(*this, filterMode);
    return *this;
}

core::raycpp::TextureUnmanaged& core::raycpp::TextureUnmanaged::SetWrap(int wrapMode) {
    ::SetTextureWrap(*this, wrapMode);
    return *this;
}

void core::raycpp::TextureUnmanaged::Draw(int posX, int posY, ::Color tint) const {
    ::DrawTexture(*this, posX, posY, tint);
}

void core::raycpp::TextureUnmanaged::Draw(::Vector2 position, ::Color tint) const {
    ::DrawTextureV(*this, position, tint);
}

void core::raycpp::TextureUnmanaged::Draw(
    ::Vector2 position,
    float     rotation,
    float     scale,
    ::Color   tint
) const {
    ::DrawTextureEx(*this, position, rotation, scale, tint);
}

void core::raycpp::TextureUnmanaged::Draw(
    ::Rectangle sourceRec,
    ::Vector2   position,
    ::Color     tint
) const {
    ::DrawTextureRec(*this, sourceRec, position, tint);
}

void core::raycpp::TextureUnmanaged::Draw(
    ::Rectangle sourceRec,
    ::Rectangle destRec,
    ::Vector2   origin,
    float       rotation,
    ::Color     tint
) const {
    ::DrawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
}

void core::raycpp::TextureUnmanaged::Draw(
    ::NPatchInfo nPatchInfo,
    ::Rectangle  destRec,
    ::Vector2    origin,
    float        rotation,
    ::Color      tint
) const {
    ::DrawTextureNPatch(*this, nPatchInfo, destRec, origin, rotation, tint);
}

void core::raycpp::TextureUnmanaged::DrawBillboard(
    const ::Camera& camera,
    ::Vector3       position,
    float           size,
    ::Color         tint
) const {
    ::DrawBillboard(camera, *this, position, size, tint);
}

void core::raycpp::TextureUnmanaged::DrawBillboard(
    const ::Camera& camera,
    ::Rectangle     source,
    ::Vector3       position,
    ::Vector2       size,
    ::Color         tint
) const {
    DrawBillboardRec(camera, *this, source, position, size, tint);
}

void core::raycpp::TextureUnmanaged::DrawBillboard(
    const ::Camera& camera,
    ::Rectangle     source,
    Vector3         position,
    ::Vector3       upv,
    Vector2         size,
    Vector2         origin,
    float           rotation,
    ::Color         tint
) const {
    DrawBillboardPro(
        camera,
        *this,
        source,
        position,
        upv,
        size,
        origin,
        rotation,
        tint
    );
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::SetMaterial(::Material* material, int mapType) {
    ::SetMaterialTexture(material, mapType, *this);
    return *this;
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::SetMaterial(const ::Material& material, int mapType) {
    ::SetMaterialTexture(
        const_cast<::Material*>(&material), //NOLINT
        mapType,
        *this
    );
    return *this;
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::SetShapes(const ::Rectangle& source) {
    ::SetShapesTexture(*this, source);
    return *this;
}

core::raycpp::TextureUnmanaged&
core::raycpp::TextureUnmanaged::SetShaderValue(const ::Shader& shader, int locIndex) {
    ::SetShaderValueTexture(shader, locIndex, *this);
    return *this;
}

bool core::raycpp::TextureUnmanaged::IsReady() const {
    return id != 0;
}

void core::raycpp::TextureUnmanaged::set(const ::Texture& texture) {
    id      = texture.id;
    width   = texture.width;
    height  = texture.height;
    mipmaps = texture.mipmaps;
    format  = texture.format;
}
