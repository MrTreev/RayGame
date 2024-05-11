#include "raylib/textureunmanaged.h"
#include "raylib/raylibexception.h"

raylib::TextureUnmanaged::TextureUnmanaged()
    : ::Texture{0, 0, 0, 0, 0} {}

raylib::TextureUnmanaged::TextureUnmanaged(
    unsigned int _id,
    int          _width,
    int          _height,
    int          _mipmaps,
    int          _format
)
    : ::Texture{_id, _width, _height, _mipmaps, _format} {}

raylib::TextureUnmanaged::TextureUnmanaged(const ::Texture& texture)
    : ::Texture{
        texture.id,
        texture.width,
        texture.height,
        texture.mipmaps,
        texture.format
    } {}

raylib::TextureUnmanaged::TextureUnmanaged(const ::Image& image) {
    Load(Image(image));
}

raylib::TextureUnmanaged::TextureUnmanaged(const ::Image& image, int layout) {
    Load(image, layout);
}

raylib::TextureUnmanaged::TextureUnmanaged(const std::string& fileName) {
    Load(fileName);
}

raylib::TextureUnmanaged::TextureUnmanaged(::Texture&& other)
    : ::Texture{
        other.id,
        other.width,
        other.height,
        other.mipmaps,
        other.format
    } {}

unsigned int raylib::TextureUnmanaged::GetId() const {
    return id;
}

int raylib::TextureUnmanaged::GetWidth() const {
    return width;
}

int raylib::TextureUnmanaged::GetHeight() const {
    return height;
}

int raylib::TextureUnmanaged::GetMipmaps() const {
    return mipmaps;
}

int raylib::TextureUnmanaged::GetFormat() const {
    return format;
}

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::operator=(const ::Texture& texture) {
    set(texture);
    return *this;
}

::Vector2 raylib::TextureUnmanaged::GetSize() const {
    return {static_cast<float>(width), static_cast<float>(height)};
}

void raylib::TextureUnmanaged::Load(const ::Image& image) {
    set(::LoadTextureFromImage(image));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from Image");
    }
}

void raylib::TextureUnmanaged::Load(const ::Image& image, int layoutType) {
    set(::LoadTextureCubemap(image, layoutType));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from Cubemap");
    }
}

void raylib::TextureUnmanaged::Load(const std::string& fileName) {
    set(::LoadTexture(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Texture from file: " + fileName);
    }
}

void raylib::TextureUnmanaged::Unload() {
    // Protect against calling UnloadTexture() twice.
    if (id != 0) {
        ::UnloadTexture(*this);
        id = 0;
    }
}

raylib::TextureUnmanaged& raylib::TextureUnmanaged::Update(const void* pixels) {
    ::UpdateTexture(*this, pixels);
    return *this;
}

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::Update(::Rectangle rec, const void* pixels) {
    UpdateTextureRec(*this, rec, pixels);
    return *this;
}

::Image raylib::TextureUnmanaged::GetData() const {
    return ::LoadImageFromTexture(*this);
}

raylib::TextureUnmanaged::operator Image() const {
    return Image(GetData());
}

raylib::TextureUnmanaged& raylib::TextureUnmanaged::GenMipmaps() {
    ::GenTextureMipmaps(this);
    return *this;
}

raylib::TextureUnmanaged& raylib::TextureUnmanaged::SetFilter(int filterMode) {
    ::SetTextureFilter(*this, filterMode);
    return *this;
}

raylib::TextureUnmanaged& raylib::TextureUnmanaged::SetWrap(int wrapMode) {
    ::SetTextureWrap(*this, wrapMode);
    return *this;
}

void raylib::TextureUnmanaged::Draw(int posX, int posY, ::Color tint) const {
    ::DrawTexture(*this, posX, posY, tint);
}

void raylib::TextureUnmanaged::Draw(::Vector2 position, ::Color tint) const {
    ::DrawTextureV(*this, position, tint);
}

void raylib::TextureUnmanaged::Draw(
    ::Vector2 position,
    float     rotation,
    float     scale,
    ::Color   tint
) const {
    ::DrawTextureEx(*this, position, rotation, scale, tint);
}

void raylib::TextureUnmanaged::Draw(
    ::Rectangle sourceRec,
    ::Vector2   position,
    ::Color     tint
) const {
    ::DrawTextureRec(*this, sourceRec, position, tint);
}

void raylib::TextureUnmanaged::Draw(
    ::Rectangle sourceRec,
    ::Rectangle destRec,
    ::Vector2   origin,
    float       rotation,
    ::Color     tint
) const {
    ::DrawTexturePro(*this, sourceRec, destRec, origin, rotation, tint);
}

void raylib::TextureUnmanaged::Draw(
    ::NPatchInfo nPatchInfo,
    ::Rectangle  destRec,
    ::Vector2    origin,
    float        rotation,
    ::Color      tint
) const {
    ::DrawTextureNPatch(*this, nPatchInfo, destRec, origin, rotation, tint);
}

void raylib::TextureUnmanaged::DrawBillboard(
    const ::Camera& camera,
    ::Vector3       position,
    float           size,
    ::Color         tint
) const {
    ::DrawBillboard(camera, *this, position, size, tint);
}

void raylib::TextureUnmanaged::DrawBillboard(
    const ::Camera& camera,
    ::Rectangle     source,
    ::Vector3       position,
    ::Vector2       size,
    ::Color         tint
) const {
    DrawBillboardRec(camera, *this, source, position, size, tint);
}

void raylib::TextureUnmanaged::DrawBillboard(
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

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::SetMaterial(::Material* material, int mapType) {
    ::SetMaterialTexture(material, mapType, *this);
    return *this;
}

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::SetMaterial(const ::Material& material, int mapType) {
    ::SetMaterialTexture(
        const_cast<::Material*>(&material), //NOLINT
        mapType,
        *this
    );
    return *this;
}

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::SetShapes(const ::Rectangle& source) {
    ::SetShapesTexture(*this, source);
    return *this;
}

raylib::TextureUnmanaged&
raylib::TextureUnmanaged::SetShaderValue(const ::Shader& shader, int locIndex) {
    ::SetShaderValueTexture(shader, locIndex, *this);
    return *this;
}

bool raylib::TextureUnmanaged::IsReady() const {
    return id != 0;
}

void raylib::TextureUnmanaged::set(const ::Texture& texture) {
    id      = texture.id;
    width   = texture.width;
    height  = texture.height;
    mipmaps = texture.mipmaps;
    format  = texture.format;
}
