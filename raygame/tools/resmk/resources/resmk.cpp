#include "raygame/tools/resmk/resources/resmk.hpp"
#include "raygame/core/io/file.hpp"
#include "raygame/tools/resmk/resources/png.hpp"
#include "raygame/tools/resmk/resources/resource.hpp"
#include <algorithm>

namespace {
std::unique_ptr<resmk::Resource> make_resource(std::filesystem::path source) {
    std::string ext = source.extension().string();
    std::ranges::transform(ext, ext.begin(), [](char cha) {
        if (cha >= 'A' && cha <= 'Z') {
            constexpr char TO_LOW{32};
            return static_cast<char>(cha + TO_LOW);
        }
        return cha;
    });
    if (ext == ".png") {
        return std::make_unique<resmk::PngFile>(std::move(source));
    }
    return std::make_unique<resmk::Resource>(std::move(source));
}
} // namespace

void resmk::resmk(
    const std::filesystem::path&              header,
    const std::vector<std::filesystem::path>& resfiles,
    const std::string&                        outer_namespace,
    const std::string&                        ns_name
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
    for (const auto& resfile: resfiles) {
        std::unique_ptr<Resource> resource{make_resource(resfile)};
        resource->process();
        hdrfile.gencode(resource->declaration());
        srcfile.gencode(resource->definition(ns_name + "::"));
    }
    hdrfile.gencode(std::format("}} // namespace {}", ns_name));
    if (!outer_namespace.empty()) {
        hdrfile.gencode(std::format("}} // namespace {}", outer_namespace));
    }
}
