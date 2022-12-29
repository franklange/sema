#pragma once

#include <sema/actions.h>
#include <sema/types.h>

namespace sema {

auto to_packet(acquire_t) -> packet_t;
auto to_packet(release_t) -> packet_t;
auto to_packet(notify_t)  -> packet_t;

auto from_packet(packet_t) -> action_t;

} // namespace sema
