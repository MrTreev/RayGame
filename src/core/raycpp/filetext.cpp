#include "core/raycpp/filetext.h"
#include <utility>

core::raycpp::FileText::FileText(FileText&& other) noexcept
    : data(other.data)
    , length(other.length) {
    other.data   = nullptr;
    other.length = 0;
}

core::raycpp::FileText& core::raycpp::FileText::operator=(FileText&& other) noexcept {
    std::swap(data, other.data);
    std::swap(length, other.length);
    return *this;
}

core::raycpp::FileText::~FileText() {
    Unload();
}

core::raycpp::FileText::FileText(const std::string& fileName) {
    Load(fileName);
}

const char* core::raycpp::FileText::GetData() const {
    return data;
}

unsigned int core::raycpp::FileText::GetLength() const {
    return length;
}

const char* core::raycpp::FileText::c_str() const {
    return data;
}

std::string core::raycpp::FileText::ToString() const {
    return data;
}

void core::raycpp::FileText::Load(const std::string& fileName) {
    Load(fileName.c_str());
}

void core::raycpp::FileText::Load(const char* fileName) {
    data   = ::LoadFileText(fileName);
    length = ::TextLength(data);
}

void core::raycpp::FileText::Unload() {
    if (data != nullptr) {
        ::UnloadFileText(data);
        data   = nullptr;
        length = 0;
    }
}
