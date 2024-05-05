#include "gui/texture.h"
#include "utils/logger.h"
#include <stdexcept>

gui::Tex2d::Tex2d(const std::string& fileName)
    : _texture(::LoadTexture(fileName.c_str())) {
    if (_texture.id == 0) {
        utils::log::fatal("Failed to create texture" + fileName);
        throw std::runtime_error("Failed to create texture");
    }
}

gui::Tex2d::~Tex2d() {
    if (_texture.id != 0) {
        ::UnloadTexture(_texture);
    }
}

void gui::Tex2d::Draw(int posX, int posY, gui::Colour tint) const {
    ::DrawTexture(_texture, posX, posY, tint.col());
}

void gui::Tex2d::Draw(
    gui::Rect    sourceRec,
    const Vec2d& position,
    gui::Colour  tint
) const {
    ::DrawTextureRec(_texture, sourceRec.rect(), position.vec(), tint.col());
}
