#pragma once

#include "core/raycpp/meshunmanaged.h"
#include "core/raycpp/model.h"
#include "core/raycpp/raylib.h"

namespace core::raycpp {
class Mesh: public MeshUnmanaged {
public:
    using MeshUnmanaged::MeshUnmanaged;
    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;
    ~Mesh();
};
} // namespace core::raycpp
