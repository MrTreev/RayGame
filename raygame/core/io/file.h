#pragma once
#include "raygame/core/types.h"
#include <cstdio>
#include <filesystem>

namespace core::io {
class File {
private:
    std::unique_ptr<std::FILE> m_file;

public:
    enum class mode : uint8_t {
        read,
        write,
        append,
        read_extended,
        write_extended,
        append_extended
    };
    explicit File(const std::filesystem::path& filename, mode mod);
    explicit File(const std::filesystem::path& filename, const char* mod);
};
} // namespace core::io
