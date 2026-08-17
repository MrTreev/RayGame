#pragma once
#include <netinet/in.h>
#include <vector>

namespace core::network {
class Connection {};

class Server {
    using fd_t   = int;
    using addr_t = sockaddr_in;

    fd_t                    m_fd{0};
    addr_t                  m_addr{};
    std::vector<Connection> m_connections;

public:
    Server();
    ~Server();
    Server(const Server&)            = default;
    Server(Server&&)                 = default;
    Server& operator=(const Server&) = default;
    Server& operator=(Server&&)      = default;
};
} // namespace core::network
