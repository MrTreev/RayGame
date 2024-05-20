#pragma once

#include "core/raycpp/boundingbox.h"
#include "core/raycpp/model.h"
#include "core/raycpp/raylib.h"
#include <string>

namespace core::raycpp {

class MeshUnmanaged: public ::Mesh {
public:
    MeshUnmanaged();
    explicit MeshUnmanaged(const ::Mesh& mesh);
    explicit MeshUnmanaged(::Mesh&& mesh);
    MeshUnmanaged& operator=(const ::Mesh& mesh);

    explicit operator core::raycpp::BoundingBox() const;
    explicit operator core::raycpp::Model();

    static ::Mesh Poly(int sides, float radius);
    static ::Mesh Plane(float width, float length, int resX, int resZ);
    static ::Mesh Cube(float width, float height, float length);
    static ::Mesh Sphere(float radius, int rings, int slices);
    static ::Mesh HemiSphere(float radius, int rings, int slices);
    static ::Mesh Cylinder(float radius, float height, int slices);
    static ::Mesh Cone(float radius, float height, int slices);
    static ::Mesh Torus(float radius, float size, int radSeg, int sides);
    static ::Mesh Knot(float radius, float size, int radSeg, int sides);
    static ::Mesh Heightmap(const ::Image& heightmap, ::Vector3 size);
    static ::Mesh Cubicmap(const ::Image& cubicmap, ::Vector3 cubeSize);

    void Unload();
    void Upload(bool dynamic = false);
    void UpdateBuffer(int index, void* data, int dataSize, int offset = 0);
    void Draw(const ::Material& material, const ::Matrix& transform) const;
    void
    Draw(const ::Material& material, ::Matrix* transforms, int instances) const;
    void Export(const std::string& fileName);

    core::raycpp::BoundingBox BoundingBox() const;
    core::raycpp::Model       LoadModelFrom() const;

    Mesh& GenTangents();

    unsigned char*  GetBoneIds() const;
    unsigned char*  GetColors() const;
    unsigned int    GetVaoId() const;
    unsigned int*   GetVboId() const;
    unsigned short* GetIndices() const;

    float* GetAnimNormals() const;
    float* GetAnimVertices() const;
    float* GetBoneWeights() const;
    float* GetNormals() const;
    float* GetTangents() const;
    float* GetTexCoords() const;
    float* GetTexCoords2() const;
    float* GetVertices() const;
    int    GetTriangleCount() const;
    int    GetVertexCount() const;

    void SetAnimNormals(float* value);
    void SetAnimVertices(float* value);
    void SetBoneIds(unsigned char* value);
    void SetBoneWeights(float* value);
    void SetColors(unsigned char* value);
    void SetIndices(unsigned short* value);
    void SetNormals(float* value);
    void SetTangents(float* value);
    void SetTexCoords(float* value);
    void SetTexCoords2(float* value);
    void SetTriangleCount(int value);
    void SetVaoId(unsigned int value);
    void SetVboId(unsigned int* value);
    void SetVertexCount(int value);
    void SetVertices(float* value);

protected:
    void set(const ::Mesh& mesh);
};
} // namespace core::raycpp
