#include "raylib/filetext.h"
#include <utility>

raylib::FileText::FileText(FileText&& other) noexcept
    : data(other.data)
    , length(other.length) {
    other.data   = nullptr;
    other.length = 0;
}

raylib::FileText& raylib::FileText::operator=(FileText&& other) noexcept {
    std::swap(data, other.data);
    std::swap(length, other.length);
    return *this;
}

raylib::FileText::~FileText() {
    Unload();
}

raylib::FileText::FileText(const std::string& fileName) {
    Load(fileName);
}

const char* raylib::FileText::GetData() const {
    return data;
}

unsigned int raylib::FileText::GetLength() const {
    return length;
}

const char* raylib::FileText::c_str() const {
    return data;
}

std::string raylib::FileText::ToString() const {
    return data;
}

void raylib::FileText::Load(const std::string& fileName) {
    Load(fileName.c_str());
}

void raylib::FileText::Load(const char* fileName) {
    data   = ::LoadFileText(fileName);
    length = ::TextLength(data);
}

void raylib::FileText::Unload() {
    if (data != nullptr) {
        ::UnloadFileText(data);
        data   = nullptr;
        length = 0;
    }
}
