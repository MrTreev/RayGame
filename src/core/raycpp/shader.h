#pragma once

#include "core/raycpp/raylib.h"
#include <string>

namespace core::raycpp {
class Shader: public ::Shader {
public:
    explicit Shader(const ::Shader& shader);
    explicit Shader(unsigned int _id, int* _locs = nullptr);
    Shader(const std::string& vsFileName, const std::string& fsFileName);
    Shader(const char* vsFileName, const char* fsFileName);
    Shader(const Shader&) = delete;
    Shader(Shader&& other) noexcept;
    static ::Shader
    Load(const std::string& vsFileName, const std::string& fsFileName);
    static ::Shader Load(const char* vsFileName, const char* fsFileName);
    static ::Shader
    LoadFromMemory(const std::string& vsCode, const std::string& fsCode);
    static ::Shader LoadFromMemory(const char* vsCode, const char* fsCode);
    unsigned int    GetId() const;
    int*            GetLocs() const;
    Shader&         operator=(const ::Shader& shader);
    Shader&         operator=(const Shader&) = delete;
    Shader&         operator=(Shader&& other) noexcept;

    ~Shader();
    void    Unload();
    Shader& BeginMode();
    Shader& EndMode();
    int     GetLocation(const std::string& uniformName) const;
    int     GetLocationAttrib(const std::string& attribName) const;
    Shader& SetValue(int uniformLoc, const void* value, int uniformType);
    Shader&
    SetValue(int uniformLoc, const void* value, int uniformType, int count);
    Shader& SetValue(int uniformLoc, const ::Matrix& mat);
    Shader& SetValue(int uniformLoc, const ::Texture2D& texture);
    bool    IsReady() const;

protected:
    void set(const ::Shader& shader);
};
} // namespace core::raycpp
