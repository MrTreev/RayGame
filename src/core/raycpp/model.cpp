#include "core/raycpp/model.h"
#include "core/raycpp/raylibexception.h"

core::raycpp::Model::Model(const ::Model& model) {
    set(model);
}

core::raycpp::Model::Model(const std::string& fileName) {
    Load(fileName);
}

core::raycpp::Model::Model(const ::Mesh& mesh) {
    Load(mesh);
}

core::raycpp::Model::~Model() {
    Unload();
}

core::raycpp::Model::Model(Model&& other) noexcept {
    set(other);

    other.meshCount     = 0;
    other.materialCount = 0;
    other.meshes        = nullptr;
    other.materials     = nullptr;
    other.meshMaterial  = nullptr;
    other.boneCount     = 0;
    other.bones         = nullptr;
    other.bindPose      = nullptr;
}

::Matrix core::raycpp::Model::GetTransform() const {
    return transform;
}

void core::raycpp::Model::SetTransform(::Matrix value) {
    transform = value;
}

int core::raycpp::Model::GetMeshCount() const {
    return meshCount;
}

void core::raycpp::Model::SetMeshCount(int value) {
    meshCount = value;
}

int core::raycpp::Model::GetMaterialCount() const {
    return materialCount;
}

void core::raycpp::Model::SetMaterialCount(int value) {
    materialCount = value;
}

::Mesh* core::raycpp::Model::GetMeshes() const {
    return meshes;
}

void core::raycpp::Model::SetMeshes(::Mesh* value) {
    meshes = value;
}

::Material* core::raycpp::Model::GetMaterials() const {
    return materials;
}

void core::raycpp::Model::SetMaterials(::Material* value) {
    materials = value;
}

int* core::raycpp::Model::GetMeshMaterial() const {
    return meshMaterial;
}

void core::raycpp::Model::SetMeshMaterial(int* value) {
    meshMaterial = value;
}

int core::raycpp::Model::GetBoneCount() const {
    return boneCount;
}

void core::raycpp::Model::SetBoneCount(int value) {
    boneCount = value;
}

::BoneInfo* core::raycpp::Model::GetBones() const {
    return bones;
}

void core::raycpp::Model::SetBones(::BoneInfo* value) {
    bones = value;
}

::Transform* core::raycpp::Model::GetBindPose() const {
    return bindPose;
}

void core::raycpp::Model::SetBindPose(::Transform* value) {
    bindPose = value;
}

core::raycpp::Model& core::raycpp::Model::operator=(const ::Model& model) {
    set(model);
    return *this;
}

core::raycpp::Model& core::raycpp::Model::operator=(Model&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.meshCount     = 0;
    other.materialCount = 0;
    other.meshes        = nullptr;
    other.materials     = nullptr;
    other.meshMaterial  = nullptr;
    other.boneCount     = 0;
    other.bones         = nullptr;
    other.bindPose      = nullptr;

    return *this;
}

void core::raycpp::Model::Unload() {
    if (meshes != nullptr || materials != nullptr) {
        ::UnloadModel(*this);
        meshes    = nullptr;
        materials = nullptr;
    }
}

core::raycpp::Model& core::raycpp::Model::SetMeshMaterial(int meshId, int materialId) {
    ::SetModelMeshMaterial(this, meshId, materialId);
    return *this;
}

core::raycpp::Model&
core::raycpp::Model::UpdateAnimation(const ::ModelAnimation& anim, int frame) {
    ::UpdateModelAnimation(*this, anim, frame);
    return *this;
}

bool core::raycpp::Model::IsModelAnimationValid(const ::ModelAnimation& anim) const {
    return ::IsModelAnimationValid(*this, anim);
}

void core::raycpp::Model::Draw(::Vector3 position, float scale, ::Color tint) const {
    ::DrawModel(*this, position, scale, tint);
}

void core::raycpp::Model::Draw(
    ::Vector3 position,
    ::Vector3 rotationAxis,
    float     rotationAngle,
    ::Vector3 scale,
    ::Color   tint
) const {
    ::DrawModelEx(*this, position, rotationAxis, rotationAngle, scale, tint);
}

void core::raycpp::Model::DrawWires(::Vector3 position, float scale, ::Color tint)
    const {
    ::DrawModelWires(*this, position, scale, tint);
}

void core::raycpp::Model::DrawWires(
    ::Vector3 position,
    ::Vector3 rotationAxis,
    float     rotationAngle,
    ::Vector3 scale,
    ::Color   tint
) const {
    ::DrawModelWiresEx(
        *this,
        position,
        rotationAxis,
        rotationAngle,
        scale,
        tint
    );
}

BoundingBox core::raycpp::Model::GetBoundingBox() const {
    return ::GetModelBoundingBox(*this);
}

core::raycpp::Model::operator BoundingBox() const {
    return ::GetModelBoundingBox(*this);
}

bool core::raycpp::Model::IsReady() const {
    return ::IsModelReady(*this);
}

void core::raycpp::Model::Load(const std::string& fileName) {
    set(::LoadModel(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Model from " + fileName);
    }
}

void core::raycpp::Model::Load(const ::Mesh& mesh) {
    set(::LoadModelFromMesh(mesh));
    if (!IsReady()) {
        throw RaylibException("Failed to load Model from Mesh");
    }
}

void core::raycpp::Model::set(const ::Model& model) {
    transform = model.transform;

    meshCount     = model.meshCount;
    materialCount = model.materialCount;
    meshes        = model.meshes;
    materials     = model.materials;
    meshMaterial  = model.meshMaterial;

    boneCount = model.boneCount;
    bones     = model.bones;
    bindPose  = model.bindPose;
}

core::raycpp::Model::Model() {}
