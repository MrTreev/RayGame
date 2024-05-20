#include "core/raycpp/meshunmanaged.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::MeshUnmanaged::MeshUnmanaged() {
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

core::raycpp::MeshUnmanaged::MeshUnmanaged(const ::Mesh& mesh) {
    set(mesh);
}

core::raycpp::MeshUnmanaged::MeshUnmanaged(::Mesh&& mesh) {
    set(mesh);
}

::Mesh core::raycpp::MeshUnmanaged::Poly(int sides, float radius) {
    return ::GenMeshPoly(sides, radius);
}

::Mesh
core::raycpp::MeshUnmanaged::Plane(float width, float length, int resX, int resZ) {
    return ::GenMeshPlane(width, length, resX, resZ);
}

::Mesh core::raycpp::MeshUnmanaged::Cube(float width, float height, float length) {
    return ::GenMeshCube(width, height, length);
}

::Mesh core::raycpp::MeshUnmanaged::Sphere(float radius, int rings, int slices) {
    return ::GenMeshSphere(radius, rings, slices);
}

::Mesh core::raycpp::MeshUnmanaged::HemiSphere(float radius, int rings, int slices) {
    return ::GenMeshHemiSphere(radius, rings, slices);
}

::Mesh core::raycpp::MeshUnmanaged::Cylinder(float radius, float height, int slices) {
    return ::GenMeshCylinder(radius, height, slices);
}

::Mesh core::raycpp::MeshUnmanaged::Cone(float radius, float height, int slices) {
    return ::GenMeshCone(radius, height, slices);
}

::Mesh
core::raycpp::MeshUnmanaged::Torus(float radius, float size, int radSeg, int sides) {
    return ::GenMeshTorus(radius, size, radSeg, sides);
}

::Mesh
core::raycpp::MeshUnmanaged::Knot(float radius, float size, int radSeg, int sides) {
    return ::GenMeshKnot(radius, size, radSeg, sides);
}

::Mesh
core::raycpp::MeshUnmanaged::Heightmap(const ::Image& heightmap, ::Vector3 size) {
    return ::GenMeshHeightmap(heightmap, size);
}

::Mesh
core::raycpp::MeshUnmanaged::Cubicmap(const ::Image& cubicmap, ::Vector3 cubeSize) {
    return ::GenMeshCubicmap(cubicmap, cubeSize);
}

core::raycpp::MeshUnmanaged& core::raycpp::MeshUnmanaged::operator=(const ::Mesh& mesh) {
    set(mesh);
    return *this;
}

core::raycpp::MeshUnmanaged::operator core::raycpp::BoundingBox() const {
    return BoundingBox();
}

core::raycpp::MeshUnmanaged::operator core::raycpp::Model() {
    return core::raycpp::Model(::LoadModelFromMesh(*this));
}

void core::raycpp::MeshUnmanaged::set(const ::Mesh& mesh) {
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

void core::raycpp::MeshUnmanaged::Unload() {
    if (vboId != nullptr) {
        ::UnloadMesh(*this);
        vboId = nullptr;
    }
}

void core::raycpp::MeshUnmanaged::Upload(bool dynamic) {
    ::UploadMesh(this, dynamic);
}

void core::raycpp::MeshUnmanaged::UpdateBuffer(
    int   index,
    void* data,
    int   dataSize,
    int   offset
) {
    ::UpdateMeshBuffer(*this, index, data, dataSize, offset);
}

void core::raycpp::MeshUnmanaged::Draw(
    const ::Material& material,
    const ::Matrix&   transform
) const {
    ::DrawMesh(*this, material, transform);
}

void core::raycpp::MeshUnmanaged::Draw(
    const ::Material& material,
    ::Matrix*         transforms,
    int               instances
) const {
    ::DrawMeshInstanced(*this, material, transforms, instances);
}

void core::raycpp::MeshUnmanaged::Export(const std::string& fileName) {
    if (!::ExportMesh(*this, fileName.c_str())) {
        throw RaylibException("Failed to export the Mesh");
    }
}

Mesh& core::raycpp::MeshUnmanaged::GenTangents() {
    ::GenMeshTangents(this);
    return *this;
}

core::raycpp::BoundingBox core::raycpp::MeshUnmanaged::BoundingBox() const {
    return core::raycpp::BoundingBox(::GetMeshBoundingBox(*this));
}

core::raycpp::Model core::raycpp::MeshUnmanaged::LoadModelFrom() const {
    return core::raycpp::Model(::LoadModelFromMesh(*this));
}

int core::raycpp::MeshUnmanaged::GetVertexCount() const {
    return vertexCount;
}

void core::raycpp::MeshUnmanaged::SetVertexCount(int value) {
    vertexCount = value;
}

int core::raycpp::MeshUnmanaged::GetTriangleCount() const {
    return triangleCount;
}

void core::raycpp::MeshUnmanaged::SetTriangleCount(int value) {
    triangleCount = value;
}

float* core::raycpp::MeshUnmanaged::GetVertices() const {
    return vertices;
}

void core::raycpp::MeshUnmanaged::SetVertices(float* value) {
    vertices = value;
}

float* core::raycpp::MeshUnmanaged::GetTexCoords() const {
    return texcoords;
}

void core::raycpp::MeshUnmanaged::SetTexCoords(float* value) {
    texcoords = value;
}

float* core::raycpp::MeshUnmanaged::GetTexCoords2() const {
    return texcoords2;
}

void core::raycpp::MeshUnmanaged::SetTexCoords2(float* value) {
    texcoords2 = value;
}

float* core::raycpp::MeshUnmanaged::GetNormals() const {
    return normals;
}

void core::raycpp::MeshUnmanaged::SetNormals(float* value) {
    normals = value;
}

float* core::raycpp::MeshUnmanaged::GetTangents() const {
    return tangents;
}

void core::raycpp::MeshUnmanaged::SetTangents(float* value) {
    tangents = value;
}

unsigned char* core::raycpp::MeshUnmanaged::GetColors() const {
    return colors;
}

void core::raycpp::MeshUnmanaged::SetColors(unsigned char* value) {
    colors = value;
}

unsigned short* core::raycpp::MeshUnmanaged::GetIndices() const {
    return indices;
}

void core::raycpp::MeshUnmanaged::SetIndices(unsigned short* value) {
    indices = value;
}

float* core::raycpp::MeshUnmanaged::GetAnimVertices() const {
    return animVertices;
}

void core::raycpp::MeshUnmanaged::SetAnimVertices(float* value) {
    animVertices = value;
}

float* core::raycpp::MeshUnmanaged::GetAnimNormals() const {
    return animNormals;
}

void core::raycpp::MeshUnmanaged::SetAnimNormals(float* value) {
    animNormals = value;
}

unsigned char* core::raycpp::MeshUnmanaged::GetBoneIds() const {
    return boneIds;
}

void core::raycpp::MeshUnmanaged::SetBoneIds(unsigned char* value) {
    boneIds = value;
}

float* core::raycpp::MeshUnmanaged::GetBoneWeights() const {
    return boneWeights;
}

void core::raycpp::MeshUnmanaged::SetBoneWeights(float* value) {
    boneWeights = value;
}

unsigned int core::raycpp::MeshUnmanaged::GetVaoId() const {
    return vaoId;
}

void core::raycpp::MeshUnmanaged::SetVaoId(unsigned int value) {
    vaoId = value;
}

unsigned int* core::raycpp::MeshUnmanaged::GetVboId() const {
    return vboId;
}

void core::raycpp::MeshUnmanaged::SetVboId(unsigned int* value) {
    vboId = value;
}
