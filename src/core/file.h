#pragma once
#include <filesystem>
#include <vector>

namespace core {

class File {
    std::filesystem::path m_path;

public:
    constexpr File(std::string fpath) {};

    constexpr std::vector<char8_t> to_vector() {};

    constexpr std::string filepath() {
        return m_path.string();
    };
};

} // namespace core
