#pragma once
#include "raygame/tools/resmk/resources/resource.hpp" // IWYU pragma: export

namespace resmk {

class PngFile: public Resource {
    int      m_width{0};
    int      m_height{0};
    int      m_channels{0};
    uint8_t* m_data{nullptr};

    static constexpr size_t N_CH = 4;

    void process_impl() override;

    [[nodiscard]]
    std::string content() const override;

    [[nodiscard]]
    std::string type() const override;

public:
    explicit PngFile(std::filesystem::path source)
        : Resource(std::move(source)) {}

    ~PngFile() override;

    PngFile(const PngFile&)            = default;
    PngFile(PngFile&&)                 = default;
    PngFile& operator=(const PngFile&) = default;
    PngFile& operator=(PngFile&&)      = default;
};

} // namespace resmk
