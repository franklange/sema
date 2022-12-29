#pragma once

#include <sema/types.h>
#include <bln_net/udp_socket.hpp>

namespace sema {

class client
{
    using socket_t = bln_net::udp::socket;

public:
    client(socket_t&, remote_t);

    void acquire();
    void release();

private:
    socket_t& m_socket;
    const remote_t m_server;
};

} // namespace sema
