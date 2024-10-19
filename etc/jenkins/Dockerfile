FROM jenkins/jenkins:2.462.3-jdk17

USER root
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y lsb-release
RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
    https://download.docker.com/linux/debian/gpg
RUN echo "deb [arch=$(dpkg --print-architecture) \
    signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
    https://download.docker.com/linux/debian \
    $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list
RUN apt-get update && apt-get install -y docker-ce-cli
RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    g++ \
    libwayland-dev \
    ninja-build \
    wayland-protocols \
    xorg-dev

RUN echo "root:password" | chpasswd

USER jenkins
RUN jenkins-plugin-cli --plugins "blueocean docker-workflow"
