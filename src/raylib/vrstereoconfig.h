#pragma once

#include "raylib/raylib.h"

namespace raylib {
class VrStereoConfig: public ::VrStereoConfig {
public:
    explicit VrStereoConfig(const ::VrDeviceInfo& info);
    VrStereoConfig(const VrStereoConfig&)            = default;
    VrStereoConfig(VrStereoConfig&&)                 = delete;
    VrStereoConfig& operator=(const VrStereoConfig&) = default;
    VrStereoConfig& operator=(VrStereoConfig&&)      = delete;
    ~VrStereoConfig();

    VrStereoConfig& BeginMode();
    VrStereoConfig& EndMode();

    void Load(const ::VrDeviceInfo& info);
    void Unload();

protected:
    void set(const ::VrStereoConfig& config);
};
} // namespace raylib
