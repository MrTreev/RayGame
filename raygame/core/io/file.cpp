#include "raygame/core/io/file.h"
#include <filesystem>
#include <system_error>

namespace core::io {
namespace {
const char* which_mode(File::mode _mode) {
    switch (_mode) {
    case File::mode::read:            return "r";
    case File::mode::write:           return "w";
    case File::mode::append:          return "a";
    case File::mode::read_extended:   return "r+";
    case File::mode::write_extended:  return "w+";
    case File::mode::append_extended: return "a+";
    }
}
} // namespace

File::File(const std::filesystem::path& filename, File::mode mod)
    : File::File(filename, which_mode(mod)) {}

File::File(const std::filesystem::path& filename, const char* mod) {
    const auto path = std::filesystem::canonical(filename);
    if (std::filesystem::exists(path)) {
        if (std::filesystem::is_regular_file(path)) {
            // NOLINTNEXTLINE(*-owning-memory) // safe, and the only way to do it
            m_file.reset(std::fopen(path.filename().c_str(), mod));
            if (m_file == nullptr) {
                throw std::system_error(errno, std::system_category());
            }
        }
    }
}

} // namespace core::io
