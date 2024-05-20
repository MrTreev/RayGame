#include "core/raycpp/mesh.h"

core::raycpp::Mesh::~Mesh() {
    Unload();
}

core::raycpp::Mesh::Mesh(Mesh&& other) noexcept {
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

core::raycpp::Mesh& core::raycpp::Mesh::operator=(Mesh&& other) noexcept {
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
