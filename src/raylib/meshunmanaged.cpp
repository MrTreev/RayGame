#include "raylib/meshunmanaged.h"
#include "raylib/raylibexception.h"

raylib::MeshUnmanaged::MeshUnmanaged() {
    vertexCount   = 0;
    triangleCount = 0;
    vertices      = nullptr;
    texcoords     = nullptr;
    texcoords2    = nullptr;
    normals       = nullptr;
    tangents      = nullptr;
    colors        = nullptr;
    indices       = nullptr;
    animVertices  = nullptr;
    animNormals   = nullptr;
    boneIds       = nullptr;
    boneWeights   = nullptr;
    vaoId         = 0;
    vboId         = nullptr;
}

raylib::MeshUnmanaged::MeshUnmanaged(const ::Mesh& mesh) {
    set(mesh);
}

raylib::MeshUnmanaged::MeshUnmanaged(::Mesh&& mesh) {
    set(mesh);
}

::Mesh raylib::MeshUnmanaged::Poly(int sides, float radius) {
    return ::GenMeshPoly(sides, radius);
}

::Mesh
raylib::MeshUnmanaged::Plane(float width, float length, int resX, int resZ) {
    return ::GenMeshPlane(width, length, resX, resZ);
}

::Mesh raylib::MeshUnmanaged::Cube(float width, float height, float length) {
    return ::GenMeshCube(width, height, length);
}

::Mesh raylib::MeshUnmanaged::Sphere(float radius, int rings, int slices) {
    return ::GenMeshSphere(radius, rings, slices);
}

::Mesh raylib::MeshUnmanaged::HemiSphere(float radius, int rings, int slices) {
    return ::GenMeshHemiSphere(radius, rings, slices);
}

::Mesh raylib::MeshUnmanaged::Cylinder(float radius, float height, int slices) {
    return ::GenMeshCylinder(radius, height, slices);
}

::Mesh raylib::MeshUnmanaged::Cone(float radius, float height, int slices) {
    return ::GenMeshCone(radius, height, slices);
}

::Mesh
raylib::MeshUnmanaged::Torus(float radius, float size, int radSeg, int sides) {
    return ::GenMeshTorus(radius, size, radSeg, sides);
}

::Mesh
raylib::MeshUnmanaged::Knot(float radius, float size, int radSeg, int sides) {
    return ::GenMeshKnot(radius, size, radSeg, sides);
}

::Mesh
raylib::MeshUnmanaged::Heightmap(const ::Image& heightmap, ::Vector3 size) {
    return ::GenMeshHeightmap(heightmap, size);
}

::Mesh
raylib::MeshUnmanaged::Cubicmap(const ::Image& cubicmap, ::Vector3 cubeSize) {
    return ::GenMeshCubicmap(cubicmap, cubeSize);
}

raylib::MeshUnmanaged& raylib::MeshUnmanaged::operator=(const ::Mesh& mesh) {
    set(mesh);
    return *this;
}

raylib::MeshUnmanaged::operator raylib::BoundingBox() const {
    return BoundingBox();
}

raylib::MeshUnmanaged::operator raylib::Model() {
    return raylib::Model(::LoadModelFromMesh(*this));
}

void raylib::MeshUnmanaged::set(const ::Mesh& mesh) {
    vertexCount   = mesh.vertexCount;
    triangleCount = mesh.triangleCount;
    vertices      = mesh.vertices;
    texcoords     = mesh.texcoords;
    texcoords2    = mesh.texcoords2;
    normals       = mesh.normals;
    tangents      = mesh.tangents;
    colors        = mesh.colors;
    indices       = mesh.indices;
    animVertices  = mesh.animVertices;
    animNormals   = mesh.animNormals;
    boneIds       = mesh.boneIds;
    boneWeights   = mesh.boneWeights;
    vaoId         = mesh.vaoId;
    vboId         = mesh.vboId;
}

void raylib::MeshUnmanaged::Unload() {
    if (vboId != nullptr) {
        ::UnloadMesh(*this);
        vboId = nullptr;
    }
}

void raylib::MeshUnmanaged::Upload(bool dynamic) {
    ::UploadMesh(this, dynamic);
}

void raylib::MeshUnmanaged::UpdateBuffer(
    int   index,
    void* data,
    int   dataSize,
    int   offset
) {
    ::UpdateMeshBuffer(*this, index, data, dataSize, offset);
}

void raylib::MeshUnmanaged::Draw(
    const ::Material& material,
    const ::Matrix&   transform
) const {
    ::DrawMesh(*this, material, transform);
}

void raylib::MeshUnmanaged::Draw(
    const ::Material& material,
    ::Matrix*         transforms,
    int               instances
) const {
    ::DrawMeshInstanced(*this, material, transforms, instances);
}

void raylib::MeshUnmanaged::Export(const std::string& fileName) {
    if (!::ExportMesh(*this, fileName.c_str())) {
        throw RaylibException("Failed to export the Mesh");
    }
}

Mesh& raylib::MeshUnmanaged::GenTangents() {
    ::GenMeshTangents(this);
    return *this;
}

raylib::BoundingBox raylib::MeshUnmanaged::BoundingBox() const {
    return raylib::BoundingBox(::GetMeshBoundingBox(*this));
}

raylib::Model raylib::MeshUnmanaged::LoadModelFrom() const {
    return raylib::Model(::LoadModelFromMesh(*this));
}

int raylib::MeshUnmanaged::GetVertexCount() const {
    return vertexCount;
}

void raylib::MeshUnmanaged::SetVertexCount(int value) {
    vertexCount = value;
}

int raylib::MeshUnmanaged::GetTriangleCount() const {
    return triangleCount;
}

void raylib::MeshUnmanaged::SetTriangleCount(int value) {
    triangleCount = value;
}

float* raylib::MeshUnmanaged::GetVertices() const {
    return vertices;
}

void raylib::MeshUnmanaged::SetVertices(float* value) {
    vertices = value;
}

float* raylib::MeshUnmanaged::GetTexCoords() const {
    return texcoords;
}

void raylib::MeshUnmanaged::SetTexCoords(float* value) {
    texcoords = value;
}

float* raylib::MeshUnmanaged::GetTexCoords2() const {
    return texcoords2;
}

void raylib::MeshUnmanaged::SetTexCoords2(float* value) {
    texcoords2 = value;
}

float* raylib::MeshUnmanaged::GetNormals() const {
    return normals;
}

void raylib::MeshUnmanaged::SetNormals(float* value) {
    normals = value;
}

float* raylib::MeshUnmanaged::GetTangents() const {
    return tangents;
}

void raylib::MeshUnmanaged::SetTangents(float* value) {
    tangents = value;
}

unsigned char* raylib::MeshUnmanaged::GetColors() const {
    return colors;
}

void raylib::MeshUnmanaged::SetColors(unsigned char* value) {
    colors = value;
}

unsigned short* raylib::MeshUnmanaged::GetIndices() const {
    return indices;
}

void raylib::MeshUnmanaged::SetIndices(unsigned short* value) {
    indices = value;
}

float* raylib::MeshUnmanaged::GetAnimVertices() const {
    return animVertices;
}

void raylib::MeshUnmanaged::SetAnimVertices(float* value) {
    animVertices = value;
}

float* raylib::MeshUnmanaged::GetAnimNormals() const {
    return animNormals;
}

void raylib::MeshUnmanaged::SetAnimNormals(float* value) {
    animNormals = value;
}

unsigned char* raylib::MeshUnmanaged::GetBoneIds() const {
    return boneIds;
}

void raylib::MeshUnmanaged::SetBoneIds(unsigned char* value) {
    boneIds = value;
}

float* raylib::MeshUnmanaged::GetBoneWeights() const {
    return boneWeights;
}

void raylib::MeshUnmanaged::SetBoneWeights(float* value) {
    boneWeights = value;
}

unsigned int raylib::MeshUnmanaged::GetVaoId() const {
    return vaoId;
}

void raylib::MeshUnmanaged::SetVaoId(unsigned int value) {
    vaoId = value;
}

unsigned int* raylib::MeshUnmanaged::GetVboId() const {
    return vboId;
}

void raylib::MeshUnmanaged::SetVboId(unsigned int* value) {
    vboId = value;
}
