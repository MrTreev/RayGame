#pragma once
#include "raygame/core/types.h"
#include <cstdio>
#include <filesystem>

namespace core::io {
class File {
private:
    std::FILE*            m_file = nullptr;
    std::filesystem::path m_path;

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
    File(File&&)                 = default;
    File& operator=(File&&)      = default;
    File(const File&)            = delete;
    File& operator=(const File&) = delete;
    ~File();

    std::FILE* raw() { return m_file; }
};
} // namespace core::io
