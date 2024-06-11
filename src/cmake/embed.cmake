# Embedding resources into files
FetchContent_Declare(
    battery-embed GIT_REPOSITORY https://github.com/batterycenter/embed.git
    GIT_TAG v1.2.15
)
FetchContent_MakeAvailable(battery-embed)
