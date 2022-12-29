#include <sema/protocol.h>

#include <bln_net/utils.hpp>

namespace sema {

auto to_packet(acquire_t a) -> packet_t
{
    return {std::move(a.client), bln_net::to_bytes("a")};
}

auto to_packet(release_t a) -> packet_t
{
    return {std::move(a.client), bln_net::to_bytes("r")};
}

auto to_packet(notify_t a) -> packet_t
{
    return {std::move(a.client), bln_net::to_bytes("n")};
}

auto from_packet(packet_t p) -> action_t
{
    const auto msg = bln_net::to_string(std::move(p.data));

    if (msg.empty())
        return detach_t{std::move(p.remote)};

    if (msg == "a")
        return acquire_t{std::move(p.remote)};

    if (msg == "r")
        return release_t{std::move(p.remote)};

    return {};
}

} // namespace sema
