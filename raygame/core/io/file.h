#pragma once
#include "raygame/core/types.h"
#include <cstdio>
#include <filesystem>
#include <string_view>

namespace core::io {
class File {
private:
    bool                  m_good = false;
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
    explicit File(std::filesystem::path filename, File::mode mod);
    explicit File(std::filesystem::path filename, const char* mod);
    File(File&&)                 = default;
    File& operator=(File&&)      = default;
    File(const File&)            = delete;
    File& operator=(const File&) = delete;
    ~File();

    std::FILE* raw() { return m_file; }

    void write(const std::string_view& msg);
    void writeln(const std::string_view& msg);

    [[nodiscard]]
    std::string fname() const;

    [[nodiscard]]
    bool good() const;
};
} // namespace core::io
