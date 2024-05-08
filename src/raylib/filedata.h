#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {

class FileData {
public:
    explicit FileData(const std::string& fileName);

    FileData()                           = default;
    FileData(const FileData&)            = delete;
    FileData& operator=(const FileData&) = delete;

    FileData(FileData&& other) noexcept;
    FileData& operator=(FileData&& other) noexcept;
    ~FileData();

    const unsigned char* GetData() const;
    int                  GetBytesRead() const;
    void                 Load(const std::string& fileName);
    void                 Load(const char* fileName);
    void                 Unload();

private:
    unsigned char* data{nullptr};
    int            bytesRead{0};
};

} // namespace raylib
