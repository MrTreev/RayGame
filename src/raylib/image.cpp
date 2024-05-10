#include "raylib/image.h"
#include "raylib/raylibexception.h"

void raylib::Image::set(const ::Image& image) {
    data    = image.data;
    width   = image.width;
    height  = image.height;
    mipmaps = image.mipmaps;
    format  = image.format;
}

raylib::Image::Image(
    void* _data,
    int   _width,
    int   _height,
    int   _mipmaps,
    int   _format
)
    : ::Image{_data, _width, _height, _mipmaps, _format} {}

raylib::Image::Image(const ::Image& image) {
    set(image);
}

raylib::Image::Image(const std::string& fileName) {
    Load(fileName);
}

raylib::Image::Image(
    const std::string& fileName,
    int                _width,
    int                _height,
    int                _format,
    int                _headerSize
) {
    Load(fileName, _width, _height, _format, _headerSize);
}

raylib::Image::Image(const std::string& fileName, int* frames) {
    Load(fileName, frames);
}

raylib::Image::Image(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize
) {
    Load(fileType, fileData, dataSize);
}

raylib::Image::Image(const ::Texture2D& texture) {
    Load(texture);
}

raylib::Image::Image(int _width, int _height, ::Color color) {
    set(::GenImageColor(_width, _height, color));
}

raylib::Image::Image(const std::string& text, int fontSize, ::Color color) {
    set(::ImageText(text.c_str(), fontSize, color));
}

raylib::Image::Image(
    const ::Font&      font,
    const std::string& text,
    float              fontSize,
    float              spacing,
    ::Color            tint
) {
    set(::ImageTextEx(font, text.c_str(), fontSize, spacing, tint));
}

raylib::Image::Image(const Image& other) {
    set(other.Copy());
}

raylib::Image::Image(Image&& other) noexcept {
    set(other);

    other.data    = nullptr;
    other.width   = 0;
    other.height  = 0;
    other.mipmaps = 0;
    other.format  = 0;
}

::Image
raylib::Image::Text(const std::string& text, int fontSize, ::Color color) {
    return ::ImageText(text.c_str(), fontSize, color);
}

::Image raylib::Image::Text(
    const ::Font&      font,
    const std::string& text,
    float              fontSize,
    float              spacing,
    ::Color            tint
) {
    return ::ImageTextEx(font, text.c_str(), fontSize, spacing, tint);
}

::Image raylib::Image::LoadFromScreen() {
    return ::LoadImageFromScreen();
}

::Image raylib::Image::Color(int _width, int _height, ::Color color) {
    return ::GenImageColor(_width, _height, color);
}

::Image raylib::Image::GradientLinear(
    int     _width,
    int     _height,
    int     _direction,
    ::Color start,
    ::Color end
) {
    return ::GenImageGradientLinear(_width, _height, _direction, start, end);
}

::Image raylib::Image::GradientRadial(
    int     _width,
    int     _height,
    float   density,
    ::Color inner,
    ::Color outer
) {
    return ::GenImageGradientRadial(_width, _height, density, inner, outer);
}

::Image raylib::Image::Checked(
    int     _width,
    int     _height,
    int     checksX,
    int     checksY,
    ::Color col1,
    ::Color col2
) {
    return ::GenImageChecked(_width, _height, checksX, checksY, col1, col2);
}

::Image raylib::Image::WhiteNoise(int _width, int _height, float factor) {
    return ::GenImageWhiteNoise(_width, _height, factor);
}

::Image raylib::Image::Cellular(int _width, int _height, int tileSize) {
    return ::GenImageCellular(_width, _height, tileSize);
}

raylib::Image::~Image() {
    Unload();
}

raylib::Image& raylib::Image::operator=(const ::Image& image) {
    set(image);
    return *this;
}

raylib::Image& raylib::Image::operator=(const Image& other) {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other.Copy());

    return *this;
}

raylib::Image& raylib::Image::operator=(Image&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.data    = nullptr;
    other.width   = 0;
    other.height  = 0;
    other.mipmaps = 0;
    other.format  = 0;

    return *this;
}

void raylib::Image::Load(const std::string& fileName) {
    set(::LoadImage(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Image from file: " + fileName);
    }
}

void raylib::Image::Load(
    const std::string& fileName,
    int                _width,
    int                _height,
    int                _format,
    int                headerSize
) {
    set(::LoadImageRaw(fileName.c_str(), _width, _height, _format, headerSize));
    if (!IsReady()) {
        throw RaylibException("Failed to load Image from file: " + fileName);
    }
}

void raylib::Image::Load(const std::string& fileName, int* frames) {
    set(::LoadImageAnim(fileName.c_str(), frames));
    if (!IsReady()) {
        throw RaylibException("Failed to load Image from file: " + fileName);
    }
}

void raylib::Image::Load(
    const std::string&   fileType,
    const unsigned char* fileData,
    int                  dataSize
) {
    set(::LoadImageFromMemory(fileType.c_str(), fileData, dataSize));
    if (!IsReady()) {
        throw RaylibException(
            "Failed to load Image data with file type: " + fileType
        );
    }
}

void raylib::Image::Load(const ::Texture2D& texture) {
    set(::LoadImageFromTexture(texture));
    if (!IsReady()) {
        throw RaylibException("Failed to load Image from texture.");
    }
}

void raylib::Image::Unload() {
    if (data != nullptr) {
        ::UnloadImage(*this);
        data = nullptr;
    }
}

void raylib::Image::Export(const std::string& fileName) const {
    if (!::ExportImage(*this, fileName.c_str())) {
        throw RaylibException(
            TextFormat("Failed to export Image to file: %s", fileName.c_str())
        );
    }
}

unsigned char*
raylib::Image::ExportToMemory(const char* fileType, int* fileSize) {
    return ::ExportImageToMemory(*this, fileType, fileSize);
}

void raylib::Image::ExportAsCode(const std::string& fileName) const {
    if (!::ExportImageAsCode(*this, fileName.c_str())) {
        throw RaylibException(TextFormat(
            "Failed to export Image code to file: %s",
            fileName.c_str()
        ));
    }
}

void* raylib::Image::GetData() const {
    return data;
}

int raylib::Image::GetWidth() const {
    return width;
}

int raylib::Image::GetHeight() const {
    return height;
}

int raylib::Image::GetMipmaps() const {
    return mipmaps;
}

int raylib::Image::GetFormat() const {
    return format;
}

void raylib::Image::SetWidth(
    int     _width,
    int     offsetX,
    int     offsetY,
    ::Color fill
) {
    ResizeCanvas(_width, height, offsetX, offsetY, fill);
}

void raylib::Image::SetHeight(
    int     _height,
    int     offsetX,
    int     offsetY,
    ::Color fill
) {
    ResizeCanvas(width, _height, offsetX, offsetY, fill);
}

::Vector2 raylib::Image::GetSize() const {
    return {static_cast<float>(width), static_cast<float>(height)};
}

::Image raylib::Image::Copy() const {
    return ::ImageCopy(*this);
}

::Image raylib::Image::FromImage(::Rectangle rec) const {
    return ::ImageFromImage(*this, rec);
}

raylib::Image& raylib::Image::Format(int newFormat) {
    ::ImageFormat(this, newFormat);
    return *this;
}

raylib::Image& raylib::Image::ToPOT(::Color fillColor) {
    ::ImageToPOT(this, fillColor);
    return *this;
}

raylib::Image& raylib::Image::Crop(::Rectangle crop) {
    ::ImageCrop(this, crop);
    return *this;
}

raylib::Image& raylib::Image::AlphaCrop(float threshold) {
    ::ImageAlphaCrop(this, threshold);
    return *this;
}

raylib::Image& raylib::Image::AlphaClear(::Color color, float threshold) {
    ::ImageAlphaClear(this, color, threshold);
    return *this;
}

raylib::Image& raylib::Image::AlphaMask(const ::Image& alphaMask) {
    ::ImageAlphaMask(this, alphaMask);
    return *this;
}

raylib::Image& raylib::Image::AlphaPremultiply() {
    ::ImageAlphaPremultiply(this);
    return *this;
}

raylib::Image& raylib::Image::Crop(int newWidth, int newHeight) {
    return Crop(0, 0, newWidth, newHeight);
}

raylib::Image& raylib::Image::Crop(::Vector2 size) {
    return Crop(0, 0, static_cast<int>(size.x), static_cast<int>(size.y));
}

raylib::Image&
raylib::Image::Crop(int offsetX, int offsetY, int newWidth, int newHeight) {
    ::Rectangle rect{
        static_cast<float>(offsetX),
        static_cast<float>(offsetY),
        static_cast<float>(newWidth),
        static_cast<float>(newHeight)
    };
    ::ImageCrop(this, rect);
    return *this;
}

raylib::Image& raylib::Image::Resize(int newWidth, int newHeight) {
    ::ImageResize(this, newWidth, newHeight);
    return *this;
}

raylib::Image& raylib::Image::ResizeNN(int newWidth, int newHeight) {
    ::ImageResizeNN(this, newWidth, newHeight);
    return *this;
}

raylib::Image& raylib::Image::ResizeCanvas(
    int     newWidth,
    int     newHeight,
    int     offsetX,
    int     offsetY,
    ::Color color
) {
    ::ImageResizeCanvas(this, newWidth, newHeight, offsetX, offsetY, color);
    return *this;
}

raylib::Image& raylib::Image::Mipmaps() {
    ::ImageMipmaps(this);
    return *this;
}

raylib::Image& raylib::Image::Dither(int rBpp, int gBpp, int bBpp, int aBpp) {
    ::ImageDither(this, rBpp, gBpp, bBpp, aBpp);
    return *this;
}

raylib::Image& raylib::Image::FlipVertical() {
    ::ImageFlipVertical(this);
    return *this;
}

raylib::Image& raylib::Image::FlipHorizontal() {
    ::ImageFlipHorizontal(this);
    return *this;
}

raylib::Image& raylib::Image::Rotate(int degrees) {
    ::ImageRotate(this, degrees);
    return *this;
}

raylib::Image& raylib::Image::RotateCW() {
    ::ImageRotateCW(this);
    return *this;
}

raylib::Image& raylib::Image::RotateCCW() {
    ::ImageRotateCCW(this);
    return *this;
}

raylib::Image& raylib::Image::ColorTint(::Color color) {
    ::ImageColorTint(this, color);
    return *this;
}

raylib::Image& raylib::Image::ColorInvert() {
    ::ImageColorInvert(this);
    return *this;
}

raylib::Image& raylib::Image::ColorGrayscale() {
    ::ImageColorGrayscale(this);
    return *this;
}

raylib::Image& raylib::Image::ColorContrast(float contrast) {
    ::ImageColorContrast(this, contrast);
    return *this;
}

raylib::Image& raylib::Image::ColorBrightness(int brightness) {
    ::ImageColorBrightness(this, brightness);
    return *this;
}

raylib::Image& raylib::Image::ColorReplace(::Color color, ::Color replace) {
    ::ImageColorReplace(this, color, replace);
    return *this;
}

Rectangle raylib::Image::GetAlphaBorder(float threshold) const {
    return ::GetImageAlphaBorder(*this, threshold);
}

raylib::Color raylib::Image::GetColor(int xpos, int ypos) const {
    return ::GetImageColor(*this, xpos, ypos);
}

raylib::Color raylib::Image::GetColor(::Vector2 position) const {
    return ::GetImageColor(
        *this,
        static_cast<int>(position.x),
        static_cast<int>(position.y)
    );
}

raylib::Image& raylib::Image::ClearBackground(::Color color) {
    ::ImageClearBackground(this, color);
    return *this;
}

void raylib::Image::DrawPixel(int posX, int posY, ::Color color) {
    ::ImageDrawPixel(this, posX, posY, color);
}

void raylib::Image::DrawPixel(::Vector2 position, ::Color color) {
    ::ImageDrawPixelV(this, position, color);
}

void raylib::Image::DrawLine(
    int     startPosX,
    int     startPosY,
    int     endPosX,
    int     endPosY,
    ::Color color
) {
    ::ImageDrawLine(this, startPosX, startPosY, endPosX, endPosY, color);
}

void raylib::Image::DrawLine(::Vector2 start, ::Vector2 end, ::Color color) {
    ::ImageDrawLineV(this, start, end, color);
}

void raylib::Image::DrawCircle(
    int     centerX,
    int     centerY,
    int     radius,
    ::Color color
) {
    ::ImageDrawCircle(this, centerX, centerY, radius, color);
}

void raylib::Image::DrawCircle(::Vector2 center, int radius, ::Color color) {
    ::ImageDrawCircleV(this, center, radius, color);
}

void raylib::Image::DrawRectangle(
    int     posX,
    int     posY,
    int     _width,
    int     _height,
    ::Color color
) {
    ::ImageDrawRectangle(this, posX, posY, _width, _height, color);
}

void raylib::Image::DrawRectangle(
    Vector2 position,
    Vector2 size,
    ::Color color
) {
    ::ImageDrawRectangleV(this, position, size, color);
}

void raylib::Image::DrawRectangle(::Rectangle rec, ::Color color) {
    ::ImageDrawRectangleRec(this, rec, color);
}

void raylib::Image::DrawRectangleLines(
    ::Rectangle rec,
    int         thick,
    ::Color     color
) {
    ::ImageDrawRectangleLines(this, rec, thick, color);
}

void raylib::Image::Draw(
    const ::Image& src,
    ::Rectangle    srcRec,
    ::Rectangle    dstRec,
    ::Color        tint
) {
    ::ImageDraw(this, src, srcRec, dstRec, tint);
}

void raylib::Image::DrawText(
    const char* text,
    ::Vector2   position,
    int         fontSize,
    ::Color     color
) {
    ::ImageDrawText(
        this,
        text,
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        fontSize,
        color
    );
}

void raylib::Image::DrawText(
    const std::string& text,
    ::Vector2          position,
    int                fontSize,
    ::Color            color
) {
    ::ImageDrawText(
        this,
        text.c_str(),
        static_cast<int>(position.x),
        static_cast<int>(position.y),
        fontSize,
        color
    );
}

void raylib::Image::DrawText(
    const std::string& text,
    int                xpos,
    int                ypos,
    int                fontSize,
    ::Color            color
) {
    ::ImageDrawText(this, text.c_str(), xpos, ypos, fontSize, color);
}

void raylib::Image::DrawText(
    const char* text,
    int         xpos,
    int         ypos,
    int         fontSize,
    ::Color     color
) {
    ::ImageDrawText(this, text, xpos, ypos, fontSize, color);
}

void raylib::Image::DrawText(
    const ::Font&      font,
    const std::string& text,
    ::Vector2          position,
    float              fontSize,
    float              spacing,
    ::Color            tint
) {
    ::ImageDrawTextEx(
        this,
        font,
        text.c_str(),
        position,
        fontSize,
        spacing,
        tint
    );
}

void raylib::Image::DrawText(
    const ::Font& font,
    const char*   text,
    ::Vector2     position,
    float         fontSize,
    float         spacing,
    ::Color       tint
) {
    ::ImageDrawTextEx(this, font, text, position, fontSize, spacing, tint);
}

::Color* raylib::Image::LoadColors() const {
    return ::LoadImageColors(*this);
}

::Color*
raylib::Image::LoadPalette(int maxPaletteSize, int* colorsCount) const {
    return ::LoadImagePalette(*this, maxPaletteSize, colorsCount);
}

void raylib::Image::UnloadColors(::Color* colors) {
    ::UnloadImageColors(colors);
}

void raylib::Image::UnloadPalette(::Color* colors) {
    ::UnloadImagePalette(colors);
}

::Texture2D raylib::Image::LoadTexture() const {
    return ::LoadTextureFromImage(*this);
}

raylib::Image::operator ::Texture2D() const {
    return LoadTexture();
}

int raylib::Image::GetPixelDataSize(int _width, int _height, int _format) {
    return ::GetPixelDataSize(_width, _height, _format);
}

int raylib::Image::GetPixelDataSize() const {
    return ::GetPixelDataSize(width, height, format);
}

bool raylib::Image::IsReady() const {
    return ::IsImageReady(*this);
}
