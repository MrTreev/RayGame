#pragma once

#include "raylib/raylib.h"
#include <string>
#include <vector>

namespace raylib {
/**
 * Model animation
 */
class ModelAnimation: public ::ModelAnimation {
public:
    ModelAnimation(const ::ModelAnimation& model);
    ModelAnimation(const ModelAnimation&) = delete;
    ModelAnimation(ModelAnimation&& other);
    ~ModelAnimation();
    static std::vector<ModelAnimation> Load(const std::string& fileName);

    ModelAnimation& operator=(const ::ModelAnimation& model);
    ModelAnimation& operator=(const ModelAnimation&) = delete;
    ModelAnimation& operator=(ModelAnimation&& other) noexcept;
    ModelAnimation& Update(const ::Model& model, int frame);
    void            Unload();
    bool            IsValid(const ::Model& model) const;

    int           GetBoneCount() const;
    void          SetBoneCount(int value);
    ::BoneInfo*   GetBones() const;
    void          SetBones(::BoneInfo* value);
    int           GetFrameCount() const;
    void          SetFrameCount(int value);
    ::Transform** GetFramePoses() const;
    void          SetFramePoses(::Transform** value);

protected:
    void set(const ::ModelAnimation& model);
};
} // namespace raylib
