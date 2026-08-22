#include "raygame/tools/resmk/resources/resmk.hpp"
#include "raygame/core/io/file.hpp"

void resmk::resmk(
    const std::filesystem::path&                  header,
    const std::vector<std::unique_ptr<Resource>>& resources,
    std::string                                   outer_namespace,
    std::string                                   ns_name
) {
    core::io::File hdrfile{header, core::io::File::mode::write};
    auto           srcname{header.string()};
    const auto     back = srcname.rfind('h');
    srcname.at(back)    = 'c';
    core::io::File srcfile{srcname, core::io::File::mode::write};
    hdrfile.gencode("#include \"raygame/core/drawing/image.hpp\"");
    hdrfile.writeln("");
    if (!outer_namespace.empty()) {
        hdrfile.gencode(std::format("namespace {} {{", outer_namespace));
    }
    hdrfile.gencode(std::format("namespace {} {{", ns_name));
    srcfile.gencode("#include \"raygame/core/drawing/image.hpp\"");
    srcfile.gencode(std::format("#include \"{}\"", header.filename().string()));
    for (const auto& resource: resources) {
        hdrfile.gencode(resource->declaration());
        srcfile.gencode(resource->definition(ns_name + "::"));
    }
    hdrfile.gencode(std::format("}} // namespace {}", ns_name));
    if (!outer_namespace.empty()) {
        hdrfile.gencode(std::format("}} // namespace {}", outer_namespace));
    }
}
