#pragma once
#include "raygame/tools/resmk/resources/resource.hpp"
#include <filesystem>
#include <vector>

namespace resmk {

void resmk(
    const std::filesystem::path&                  header,
    const std::vector<std::unique_ptr<Resource>>& m_resources,
    std::string                                   m_outer_namespace,
    std::string                                   m_ns_name
);

} // namespace resmk
