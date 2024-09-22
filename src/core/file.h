#pragma once
#include <filesystem>
#include <fstream>
#include <vector>

namespace core {

enum class OpenMode {
    ReadOnly,
    WriteOnly,
    ReadWrite,
};

class File {
    std::filesystem::path m_path;
    std::fstream          m_fstream;

public:
    File(std::filesystem::path fpath, OpenMode mode = OpenMode::ReadOnly);
    ~File();

    std::vector<char8_t>  to_vector();
    std::filesystem::path filepath();
};

} // namespace core
