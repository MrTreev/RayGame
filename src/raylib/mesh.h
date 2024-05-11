#pragma once

#include "raylib/meshunmanaged.h"
#include "raylib/model.h"
#include "raylib/raylib-cpp-utils.h"
#include "raylib/raylib.h"

namespace raylib {
class Mesh: public MeshUnmanaged {
public:
    using MeshUnmanaged::MeshUnmanaged;
    Mesh(const Mesh&)            = delete;
    Mesh& operator=(const Mesh&) = delete;

    ~Mesh() {
        Unload();
    }

    Mesh(Mesh&& other)  noexcept {
        set(other);

        other.vertexCount   = 0;
        other.triangleCount = 0;
        other.vertices      = nullptr;
        other.texcoords     = nullptr;
        other.texcoords2    = nullptr;
        other.normals       = nullptr;
        other.tangents      = nullptr;
        other.colors        = nullptr;
        other.indices       = nullptr;
        other.animVertices  = nullptr;
        other.animNormals   = nullptr;
        other.boneIds       = nullptr;
        other.boneWeights   = nullptr;
        other.vaoId         = 0;
        other.vboId         = nullptr;
    }

    Mesh& operator=(Mesh&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        Unload();
        set(other);

        other.vertexCount   = 0;
        other.triangleCount = 0;
        other.vertices      = nullptr;
        other.texcoords     = nullptr;
        other.texcoords2    = nullptr;
        other.normals       = nullptr;
        other.tangents      = nullptr;
        other.colors        = nullptr;
        other.indices       = nullptr;
        other.animVertices  = nullptr;
        other.animNormals   = nullptr;
        other.boneIds       = nullptr;
        other.boneWeights   = nullptr;
        other.vaoId         = 0;
        other.vboId         = nullptr;

        return *this;
    }
};
} // namespace raylib
