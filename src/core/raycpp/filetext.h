#pragma once

#include "core/raycpp/raylib.h"
#include <string>

namespace core::raycpp {

class FileText {
public:
    explicit FileText(const std::string& fileName);

    FileText()                           = default;
    FileText(const FileText&)            = delete;
    FileText& operator=(const FileText&) = delete;

    FileText(FileText&& other) noexcept;
    FileText& operator=(FileText&& other) noexcept;
    ~FileText();

    void Load(const std::string& fileName);
    void Load(const char* fileName);
    void Unload();

    unsigned int GetLength() const;
    const char*  GetData() const;
    const char*  c_str() const;
    std::string  ToString() const;

    explicit operator std::string() const {
        return data;
    }

private:
    char*        data{nullptr};
    unsigned int length{0};
};

} // namespace core::raycpp
