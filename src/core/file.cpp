#include "core/file.h" // IWYU pragma: keep
#if 0
core::File::File(std::filesystem::path fpath, OpenMode mode)
    : m_path(std::move(fpath))
    , m_fstream() {}

core::File::~File() {}

std::vector<char8_t> core::File::to_vector() {}

std::filesystem::path core::File::filepath() {
    return m_path;
}
#endif
