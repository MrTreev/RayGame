#include "raygame/tools/resmk/resources/resource.h"
#include "raygame/core/condition.h"
#include "raygame/core/config.h"
#include "raygame/core/exception.h"
#include "raygame/core/logger.h"
#include <format>
#include <string>

RAYGAME_CLANG_SUPPRESS_WARNING_PUSH
RAYGAME_CLANG_SUPPRESS_WARNING("-Wmissing-noreturn")

void Resource::process_impl() {
    throw core::exception::Unimplemented(
        std::format("Unknown file extension: {}", m_source.extension().string())
    );
}

RAYGAME_CLANG_SUPPRESS_WARNING_POP
[[nodiscard]]
std::string Resource::type() const {
    core::condition::unimplemented();
}

void Resource::content([[maybe_unused]] std::string& stuff) const {
    core::condition::unimplemented();
}

[[nodiscard]]
std::string Resource::declaration() const {
    return std::format("extern const {} {};", type(), m_name);
}

[[nodiscard]]
std::string Resource::definition(std::string prefix) const {
    std::string definition{};
    definition += "RAYGAME_CLANG_SUPPRESS_WARNING_PUSH\n";
    definition += "RAYGAME_CLANG_SUPPRESS_WARNING(\"-Wglobal-constructors\")\n";
    definition += "// NOLINTNEXTLINE(cert-err58-cpp)\n";
    definition += std::format("const {} {}{} {{\n", type(), prefix, m_name);
    content(definition);
    definition += std::format("\n}};\n");
    definition += "RAYGAME_CLANG_SUPPRESS_WARNING_POP\n";
    return definition;
}

void Resource::process() {
    core::log::debug("Processing: {}", m_name);
    process_impl();
}

FileError::FileError(const std ::string& message)
    : core::exception::Exception(message) {}

FileError::~FileError() noexcept = default;
