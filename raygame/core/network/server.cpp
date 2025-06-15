#include "raygame/core/network/server.h"
#include "raygame/core/logger.h"
#include <arpa/inet.h>
#include <cstdio>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

namespace {
constexpr size_t BUF_SIZE = 1024;
} // namespace

core::network::Server::Server()
    : m_fd(socket(PF_INET, SOCK_STREAM, 0)) {
    m_addr.sin_family      = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_fd, reinterpret_cast<sockaddr*>(&m_addr), sizeof(m_addr)) != 0) {
        perror("bind error:");
        return;
    }

    // read port
    socklen_t addr_len = sizeof(m_addr);
    getsockname(m_fd, reinterpret_cast<sockaddr*>(&m_addr), &addr_len);
    core::log::debug("server is on port %d\n", static_cast<int>(ntohs(m_addr.sin_port)));

    if (listen(m_fd, 1) != 0) {
        perror("listen error:");
        return;
    }

    // accept incoming connection
    sockaddr_storage caddr{};
    socklen_t        caddr_len = sizeof(caddr);
    const int        cfd       = accept(m_fd, reinterpret_cast<sockaddr*>(&caddr), &caddr_len);

    // read from client with recv!
    std::array<char, BUF_SIZE> buf{};
    recv(cfd, buf.data(), sizeof(buf), 0);

    // print without looking
    core::log::debug("client says:\n    %s\n", buf);
}

core::network::Server::~Server() {
    close(cfd);
    close(m_fd);
}
