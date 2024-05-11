#pragma once

#include "raylib/raylib.h"
#include <string>

namespace raylib {
class Mesh;

/**
 * Model type
 */
class Model: public ::Model {
public:
    Model();

    explicit Model(const ::Model& model);
    explicit Model(const std::string& fileName);
    explicit Model(const ::Mesh& mesh);
    Model(const raylib::Mesh& mesh) = delete;
    ~Model();
    Model(const Model&) = delete;
    Model(Model&& other) noexcept;
    ::Matrix     GetTransform() const;
    void         SetTransform(::Matrix value);
    int          GetMeshCount() const;
    void         SetMeshCount(int value);
    int          GetMaterialCount() const;
    void         SetMaterialCount(int value);
    ::Mesh*      GetMeshes() const;
    void         SetMeshes(::Mesh* value);
    ::Material*  GetMaterials() const;
    void         SetMaterials(::Material* value);
    int*         GetMeshMaterial() const;
    void         SetMeshMaterial(int* value);
    int          GetBoneCount() const;
    void         SetBoneCount(int value);
    ::BoneInfo*  GetBones() const;
    void         SetBones(::BoneInfo* value);
    ::Transform* GetBindPose() const;
    void         SetBindPose(::Transform* value);
    Model&       operator=(const ::Model& model);
    Model&       operator=(const Model&) = delete;
    Model&       operator=(Model&& other) noexcept;
    void         Unload();
    Model&       SetMeshMaterial(int meshId, int materialId);
    Model&       UpdateAnimation(const ::ModelAnimation& anim, int frame);
    bool         IsModelAnimationValid(const ::ModelAnimation& anim) const;
    void         Draw(
                ::Vector3 position,
                float     scale = 1.0F,
                ::Color   tint  = {255, 255, 255, 255}
            ) const;
    void Draw(
        ::Vector3 position,
        ::Vector3 rotationAxis,
        float     rotationAngle = 0.0F,
        ::Vector3 scale         = {1.0F, 1.0F, 1.0F},
        ::Color   tint          = {255, 255, 255, 255}
    ) const;
    void DrawWires(
        ::Vector3 position,
        float     scale = 1.0F,
        ::Color   tint  = {255, 255, 255, 255}
    ) const;
    void DrawWires(
        ::Vector3 position,
        ::Vector3 rotationAxis,
        float     rotationAngle = 0.0F,
        ::Vector3 scale         = {1.0F, 1.0F, 1.0F},
        ::Color   tint          = {255, 255, 255, 255}
    ) const;
    BoundingBox GetBoundingBox() const;
    explicit    operator BoundingBox() const;
    bool        IsReady() const;
    void        Load(const std::string& fileName);
    void        Load(const ::Mesh& mesh);

protected:
    void set(const ::Model& model);
};
} // namespace raylib
