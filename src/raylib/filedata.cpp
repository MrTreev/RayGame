#include "raylib/filedata.h"
#include <utility>

raylib::FileData::FileData(FileData&& other) noexcept
    : data(other.data)
    , bytesRead(other.bytesRead) {
    other.data      = nullptr;
    other.bytesRead = 0;
}

raylib::FileData& raylib::FileData::operator=(FileData&& other) noexcept {
    std::swap(data, other.data);
    std::swap(bytesRead, other.bytesRead);
    return *this;
}

raylib::FileData::~FileData() {
    Unload();
}

raylib::FileData::FileData(const std::string& fileName) {
    Load(fileName);
}

const unsigned char* raylib::FileData::GetData() const {
    return data;
}

int raylib::FileData::GetBytesRead() const {
    return bytesRead;
}

void raylib::FileData::Load(const std::string& fileName) {
    Load(fileName.c_str());
}

void raylib::FileData::Load(const char* fileName) {
    data = ::LoadFileData(fileName, &bytesRead);
}

void raylib::FileData::Unload() {
    if (data != nullptr) {
        ::UnloadFileData(data);
        data = nullptr;
    }
}
