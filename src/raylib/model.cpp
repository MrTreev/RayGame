#include "model.h"

raylib::Model::Model(const ::Model& model) {
    set(model);
}

raylib::Model::Model(const std::string& fileName) {
    Load(fileName);
}

raylib::Model::Model(const ::Mesh& mesh) {
    Load(mesh);
}

raylib::Model::~Model() {
    Unload();
}

raylib::Model::Model(Model&& other) noexcept {
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

::Matrix raylib::Model::GetTransform() const {
    return transform;
}

void raylib::Model::SetTransform(::Matrix value) {
    transform = value;
}

int raylib::Model::GetMeshCount() const {
    return meshCount;
}

void raylib::Model::SetMeshCount(int value) {
    meshCount = value;
}

int raylib::Model::GetMaterialCount() const {
    return materialCount;
}

void raylib::Model::SetMaterialCount(int value) {
    materialCount = value;
}

::Mesh* raylib::Model::GetMeshes() const {
    return meshes;
}

void raylib::Model::SetMeshes(::Mesh* value) {
    meshes = value;
}

::Material* raylib::Model::GetMaterials() const {
    return materials;
}

void raylib::Model::SetMaterials(::Material* value) {
    materials = value;
}

int* raylib::Model::GetMeshMaterial() const {
    return meshMaterial;
}

void raylib::Model::SetMeshMaterial(int* value) {
    meshMaterial = value;
}

int raylib::Model::GetBoneCount() const {
    return boneCount;
}

void raylib::Model::SetBoneCount(int value) {
    boneCount = value;
}

::BoneInfo* raylib::Model::GetBones() const {
    return bones;
}

void raylib::Model::SetBones(::BoneInfo* value) {
    bones = value;
}

::Transform* raylib::Model::GetBindPose() const {
    return bindPose;
}

void raylib::Model::SetBindPose(::Transform* value) {
    bindPose = value;
}

raylib::Model& raylib::Model::operator=(const ::Model& model) {
    set(model);
    return *this;
}

raylib::Model& raylib::Model::operator=(Model&& other) noexcept {
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

void raylib::Model::Unload() {
    if (meshes != nullptr || materials != nullptr) {
        ::UnloadModel(*this);
        meshes    = nullptr;
        materials = nullptr;
    }
}

raylib::Model& raylib::Model::SetMeshMaterial(int meshId, int materialId) {
    ::SetModelMeshMaterial(this, meshId, materialId);
    return *this;
}

raylib::Model&
raylib::Model::UpdateAnimation(const ::ModelAnimation& anim, int frame) {
    ::UpdateModelAnimation(*this, anim, frame);
    return *this;
}

bool raylib::Model::IsModelAnimationValid(const ::ModelAnimation& anim) const {
    return ::IsModelAnimationValid(*this, anim);
}

void raylib::Model::Draw(::Vector3 position, float scale, ::Color tint) const {
    ::DrawModel(*this, position, scale, tint);
}

void raylib::Model::Draw(
    ::Vector3 position,
    ::Vector3 rotationAxis,
    float     rotationAngle,
    ::Vector3 scale,
    ::Color   tint
) const {
    ::DrawModelEx(*this, position, rotationAxis, rotationAngle, scale, tint);
}

void raylib::Model::DrawWires(::Vector3 position, float scale, ::Color tint)
    const {
    ::DrawModelWires(*this, position, scale, tint);
}

void raylib::Model::DrawWires(
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

BoundingBox raylib::Model::GetBoundingBox() const {
    return ::GetModelBoundingBox(*this);
}

explicit raylib::Model::operator BoundingBox() const {
    return ::GetModelBoundingBox(*this);
}

bool raylib::Model::IsReady() const {
    return ::IsModelReady(*this);
}

void raylib::Model::Load(const std::string& fileName) {
    set(::LoadModel(fileName.c_str()));
    if (!IsReady()) {
        throw RaylibException("Failed to load Model from " + fileName);
    }
}

void raylib::Model::Load(const ::Mesh& mesh) {
    set(::LoadModelFromMesh(mesh));
    if (!IsReady()) {
        throw RaylibException("Failed to load Model from Mesh");
    }
}

void raylib::Model::set(const ::Model& model) {
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
