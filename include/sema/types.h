#pragma once

#include <bln_net/udp.hpp>

#include <cstdint>
#include <vector>

namespace sema {

using bytes_t   = bln_net::bytes;
using packet_t  = bln_net::udp::packet;
using remote_t  = bln_net::udp::endpoint;
using remotes_t = std::vector<remote_t>;
using timeout_t = bln_net::timeout;

using srv_sock_t = bln_net::udp::socket_hb_srv;
using cli_sock_t = bln_net::udp::socket_hb_cli;

} // namespace sema
