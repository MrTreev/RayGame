#pragma once

#include "raylib/raylib-cpp-utils.h"
#include "raylib/raylib.h"

namespace raylib {
class VrStereoConfig: public ::VrStereoConfig {
public:
    VrStereoConfig(const ::VrDeviceInfo& info) {
        Load(info);
    }

    void Load(const ::VrDeviceInfo& info) {
        set(LoadVrStereoConfig(info));
    }

    ~VrStereoConfig() {
        Unload();
    }

    VrStereoConfig& BeginMode() {
        ::BeginVrStereoMode(*this);
        return *this;
    }

    VrStereoConfig& EndMode() {
        ::EndVrStereoMode();
        return *this;
    }

    void Unload() {
        ::UnloadVrStereoConfig(*this);
    }

protected:
    void set(const ::VrStereoConfig& config) {
        projection[0]        = config.projection[0];
        projection[1]        = config.projection[1];
        viewOffset[0]        = config.viewOffset[0];
        viewOffset[1]        = config.viewOffset[1];
        leftLensCenter[0]    = config.leftLensCenter[0];
        leftLensCenter[1]    = config.leftLensCenter[1];
        rightLensCenter[0]   = config.rightLensCenter[0];
        rightLensCenter[1]   = config.rightLensCenter[1];
        leftScreenCenter[0]  = config.leftScreenCenter[0];
        leftScreenCenter[1]  = config.leftScreenCenter[1];
        rightScreenCenter[0] = config.rightScreenCenter[0];
        rightScreenCenter[1] = config.rightScreenCenter[1];
        scale[0]             = config.scale[0];
        scale[1]             = config.scale[1];
        scaleIn[0]           = config.scaleIn[0];
        scaleIn[1]           = config.scaleIn[1];
    }
};
} // namespace raylib
