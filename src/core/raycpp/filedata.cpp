#include "core/raycpp/filedata.h"
#include <utility>

core::raycpp::FileData::FileData(FileData&& other) noexcept
    : data(other.data)
    , bytesRead(other.bytesRead) {
    other.data      = nullptr;
    other.bytesRead = 0;
}

core::raycpp::FileData& core::raycpp::FileData::operator=(FileData&& other) noexcept {
    std::swap(data, other.data);
    std::swap(bytesRead, other.bytesRead);
    return *this;
}

core::raycpp::FileData::~FileData() {
    Unload();
}

core::raycpp::FileData::FileData(const std::string& fileName) {
    Load(fileName);
}

const unsigned char* core::raycpp::FileData::GetData() const {
    return data;
}

int core::raycpp::FileData::GetBytesRead() const {
    return bytesRead;
}

void core::raycpp::FileData::Load(const std::string& fileName) {
    Load(fileName.c_str());
}

void core::raycpp::FileData::Load(const char* fileName) {
    data = ::LoadFileData(fileName, &bytesRead);
}

void core::raycpp::FileData::Unload() {
    if (data != nullptr) {
        ::UnloadFileData(data);
        data = nullptr;
    }
}
