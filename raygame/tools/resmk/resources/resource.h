#pragma once
#include "raygame/core/exception.h"
#include <filesystem>

class FileError: public core::exception::Exception {
public:
    FileError(const FileError&)            = default;
    FileError(FileError&&)                 = delete;
    FileError& operator=(const FileError&) = default;
    FileError& operator=(FileError&&)      = delete;
    explicit FileError(const std::string& message);
    ~FileError() noexcept override;
};

class Resource {
    virtual void process_impl();
    [[nodiscard]]
    virtual std::string type() const;
    virtual void        content([[maybe_unused]] std::string& stuff) const;

public:
    std::filesystem::path m_source; // NOLINT(misc-non-private-member-variables-in-classes)
    std::string           m_name;   // NOLINT(misc-non-private-member-variables-in-classes)

    virtual ~Resource()                  = default;
    Resource(const Resource&)            = default;
    Resource(Resource&&)                 = default;
    Resource& operator=(const Resource&) = default;
    Resource& operator=(Resource&&)      = default;

    explicit Resource(std::filesystem::path source)
        : m_source(std::move(source))
        , m_name(m_source.stem().string()) {}

    [[nodiscard]]
    std::string declaration() const;

    [[nodiscard]]
    std::string definition(std::string prefix) const;

    void process();
};
