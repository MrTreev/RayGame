#include "core/config.h"
#include <string>
#if defined(RAYGAME_OS_LINUX)
#    include <sys/socket.h>
#    include <sys/un.h>
#endif

class Socket {
public:
    explicit Socket();
    ~Socket();
    Socket(const Socket&)            = delete;
    Socket(Socket&&)                 = delete;
    Socket& operator=(const Socket&) = delete;
    Socket& operator=(Socket&&)      = delete;

protected:
    void connect();

private:
    int             _fd{0};
    struct sockaddr _sockaddr;
};

#if defined(RAYGAME_OS_LINUX)
class UnixSocket: public Socket {
public:
    explicit UnixSocket(const std::string& sock_name);

protected:
    void connect();

private:
    int _fd{0};

    struct sockaddr_un _sockaddr {
        .sun_family = AF_UNIX,
    };
};
#endif
