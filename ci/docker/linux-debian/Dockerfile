FROM jenkins/agent:latest as raygame-linux-debian

ENV TZ=Australia/Melbourne

RUN ln -snf /usr/share/zoneinfo/"${TZ}" /etc/localtime \
    && echo "${TZ}" > /etc/timezone \
    && dpkg-reconfigure -f noninteractive tzdata \
    && apt-get install \
        clang-19 \
        clang-format-19 \
        clang-tidy-19 \
        clang-tools-19 \
        gcc-12 \
        libc++-19-dev \
        libc++abi-19-dev \
        libclang-19-dev \
        libclang-19-dev \
        libclang-cpp19-dev \
        libclang-rt-19-dev \
        libgcc-12-dev \
        libstdc++-12-dev \
    && :
