#pragma once
#include "core/types.h"
#include <string>

class SpriteSheet {
private:

public:
    SpriteSheet(
        const std::string& filename,
        const uint32_t&    width,
        const uint32_t&    height
    );
};
