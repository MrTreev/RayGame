#include "raylib/modelanimation.h"

raylib::ModelAnimation::ModelAnimation(const ::ModelAnimation& model) {
    set(model);
}

raylib::ModelAnimation::ModelAnimation(ModelAnimation&& other) noexcept {
    set(other);

    other.boneCount  = 0;
    other.frameCount = 0;
    other.bones      = nullptr;
    other.framePoses = nullptr;
}

raylib::ModelAnimation::~ModelAnimation() {
    Unload();
}

std::vector<raylib::ModelAnimation>
raylib::ModelAnimation::Load(const std::string& fileName) {
    int               count = 0;
    ::ModelAnimation* modelAnimations =
        ::LoadModelAnimations(fileName.c_str(), &count);
    std::vector<raylib::ModelAnimation> mats(
        modelAnimations,
        modelAnimations + count
    );

    RL_FREE(modelAnimations);

    return mats;
}

int raylib::ModelAnimation::GetBoneCount() const {
    return boneCount;
}

void raylib::ModelAnimation::SetBoneCount(int value) {
    boneCount = value;
}

::BoneInfo* raylib::ModelAnimation::GetBones() const {
    return bones;
}

void raylib::ModelAnimation::SetBones(::BoneInfo* value) {
    bones = value;
}

int raylib::ModelAnimation::GetFrameCount() const {
    return frameCount;
}

void raylib::ModelAnimation::SetFrameCount(int value) {
    frameCount = value;
}

::Transform** raylib::ModelAnimation::GetFramePoses() const {
    return framePoses;
}

void raylib::ModelAnimation::SetFramePoses(::Transform** value) {
    framePoses = value;
}

raylib::ModelAnimation&
raylib::ModelAnimation::operator=(const ::ModelAnimation& model) {
    set(model);
    return *this;
}

raylib::ModelAnimation& raylib::ModelAnimation::operator=(ModelAnimation&& other
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

void raylib::ModelAnimation::Unload() {
    ::UnloadModelAnimation(*this);
}

raylib::ModelAnimation&
raylib::ModelAnimation::Update(const ::Model& model, int frame) {
    ::UpdateModelAnimation(model, *this, frame);
    return *this;
}

bool raylib::ModelAnimation::IsValid(const ::Model& model) const {
    return ::IsModelAnimationValid(model, *this);
}

void raylib::ModelAnimation::set(const ::ModelAnimation& model) {
    boneCount  = model.boneCount;
    frameCount = model.frameCount;
    bones      = model.bones;
    framePoses = model.framePoses;
}
