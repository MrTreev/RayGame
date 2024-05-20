#pragma once

#include "core/raycpp/raylib.h"

namespace core::raycpp {
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
} // namespace core::raycpp
