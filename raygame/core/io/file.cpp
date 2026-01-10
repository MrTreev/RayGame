#include "raygame/core/io/file.h"
#include "raygame/core/condition.h"
#include "raygame/core/logger.h"
#include "raygame/core/types.h"
#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <string>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

namespace core::io {
namespace {
const char* mod_to_cstr(File::mode mod) {
    switch (mod) {
    case File::mode::read:            return "r";
    case File::mode::write:           return "w";
    case File::mode::append:          return "a";
    case File::mode::read_extended:   return "r+";
    case File::mode::write_extended:  return "w+";
    case File::mode::append_extended: return "a+";
    }
}

File::mode cstr_to_mod(const char* mod) {
    //NOLINTBEGIN(*-pointer-arithmetic)
    if (mod[0] == 'r') {
        if (mod[1] == '+') {
            return File::mode::read_extended;
        }
        return File::mode::read;
    }
    if (mod[0] == 'w') {
        if (mod[1] == '+') {
            return File::mode::write_extended;
        }
        return File::mode::write;
    }
    if (mod[0] == 'a') {
        if (mod[1] == '+') {
            return File::mode::append_extended;
        }
        return File::mode::append;
    }
    //NOLINTEND(*-pointer-arithmetic)
    log::error("Invalid mode string: '{}'", mod);
    core::condition::unreachable();
}
} // namespace

File::File(std::filesystem::path filename, File::mode mod)
    : m_path(std::move(filename)) {
    if (mod == mode::read || mod == mode::read_extended) {
        if (std::filesystem::exists(m_path)) {
            if (std::filesystem::is_regular_file(m_path)) {
                // NOLINTNEXTLINE(*-owning-memory)
                m_file = std::fopen(m_path.c_str(), mod_to_cstr(mod));
                if (m_file == nullptr) {
                    log::error("Error in file: {}", m_path.string());
                    throw std::system_error(errno, std::system_category());
                }
            } else {
                log::error("File is not regular: {}", m_path.string());
            }
            m_good = true;
            log::trace("File opened: {}", m_path.string());
        } else {
            log::error("File does not exist: {}", m_path.string());
        }
    } else {
        // NOLINTNEXTLINE(*-owning-memory)
        m_file = std::fopen(m_path.c_str(), mod_to_cstr(mod));
        if (m_file == nullptr) {
            log::error("File: '{}'", m_path.c_str());
            log::error("Error in file: {}", m_path.string());
            throw std::system_error(errno, std::system_category());
        }
    }
}

File::File(std::filesystem::path filename, const char* mod)
    : File::File(std::move(filename), cstr_to_mod(mod)) {}

std::string File::fname() const {
    return m_path.filename().string();
}

bool File::good() const {
    return m_good;
}

void File::write(const std::string_view& msg) {
    const size_t n_written = std::fwrite(msg.data(), sizeof(msg[0]), msg.size(), m_file);
    if (n_written != msg.size()) {
        log::error("Message not fully written to: {}", m_path.filename().string());
    }
}

void File::write(const std::vector<byte>& msg) {
    const size_t n_written = std::fwrite(msg.data(), sizeof(msg[0]), msg.size(), m_file);
    if (n_written != msg.size()) {
        log::error("Message not fully written to: {}", m_path.filename().string());
    }
}

void File::writeln(const std::string_view& msg) {
    write(std::format("{}\n", msg));
}

void File::gencode(const std::string_view& msg, std::source_location loc) {
    write(std::format("{} // {}\n", msg, debug::location_message(loc)));
}

File::~File() {
    if (m_file != nullptr) {
        if (std::fflush(m_file) != 0) {
            log::error("Could not flush file: {}", m_path.string());
        }
        if (std::fclose(m_file) != 0) { // NOLINT(*-owning-memory)
            log::error("Could not close file: {}", m_path.string());
        }
        log::trace("File closed: {}", m_path.string());
        m_file = nullptr;
    }
}
} // namespace core::io
