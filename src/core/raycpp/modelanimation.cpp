#include "core/raycpp/modelanimation.h"

core::raycpp::ModelAnimation::ModelAnimation(const ::ModelAnimation& model) {
    set(model);
}

core::raycpp::ModelAnimation::ModelAnimation(ModelAnimation&& other) noexcept {
    set(other);

    other.boneCount  = 0;
    other.frameCount = 0;
    other.bones      = nullptr;
    other.framePoses = nullptr;
}

core::raycpp::ModelAnimation::~ModelAnimation() {
    Unload();
}

std::vector<core::raycpp::ModelAnimation>
core::raycpp::ModelAnimation::Load(const std::string& fileName) {
    int               count = 0;
    ::ModelAnimation* modelAnimations =
        ::LoadModelAnimations(fileName.c_str(), &count);
    std::vector<core::raycpp::ModelAnimation> mats(
        modelAnimations,
        modelAnimations + count
    );

    RL_FREE(modelAnimations);

    return mats;
}

int core::raycpp::ModelAnimation::GetBoneCount() const {
    return boneCount;
}

void core::raycpp::ModelAnimation::SetBoneCount(int value) {
    boneCount = value;
}

::BoneInfo* core::raycpp::ModelAnimation::GetBones() const {
    return bones;
}

void core::raycpp::ModelAnimation::SetBones(::BoneInfo* value) {
    bones = value;
}

int core::raycpp::ModelAnimation::GetFrameCount() const {
    return frameCount;
}

void core::raycpp::ModelAnimation::SetFrameCount(int value) {
    frameCount = value;
}

::Transform** core::raycpp::ModelAnimation::GetFramePoses() const {
    return framePoses;
}

void core::raycpp::ModelAnimation::SetFramePoses(::Transform** value) {
    framePoses = value;
}

core::raycpp::ModelAnimation&
core::raycpp::ModelAnimation::operator=(const ::ModelAnimation& model) {
    set(model);
    return *this;
}

core::raycpp::ModelAnimation& core::raycpp::ModelAnimation::operator=(ModelAnimation&& other
) noexcept {
    if (this == &other) {
        return *this;
    }

    Unload();
    set(other);

    other.boneCount  = 0;
    other.frameCount = 0;
    other.bones      = nullptr;
    other.framePoses = nullptr;

    return *this;
}

void core::raycpp::ModelAnimation::Unload() {
    ::UnloadModelAnimation(*this);
}

core::raycpp::ModelAnimation&
core::raycpp::ModelAnimation::Update(const ::Model& model, int frame) {
    ::UpdateModelAnimation(model, *this, frame);
    return *this;
}

bool core::raycpp::ModelAnimation::IsValid(const ::Model& model) const {
    return ::IsModelAnimationValid(model, *this);
}

void core::raycpp::ModelAnimation::set(const ::ModelAnimation& model) {
    boneCount  = model.boneCount;
    frameCount = model.frameCount;
    bones      = model.bones;
    framePoses = model.framePoses;
}
