#pragma once

#include "raylib/meshunmanaged.h"
#include "raylib/model.h"
#include "raylib/raylib.h"

namespace raylib {
class Mesh: public MeshUnmanaged {
public:
    using MeshUnmanaged::MeshUnmanaged;
    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();
};
} // namespace raylib
