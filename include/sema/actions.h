#pragma once

#include <sema/types.h>

#include <bln_queue/msg_queue.hpp>

#include <variant>

namespace sema {

struct acquire_t
{
    remote_t client;
    auto operator<=>(const acquire_t&) const = default;
};

struct release_t
{
    remote_t client;
    auto operator<=>(const release_t&) const = default;
};

struct notify_t
{
    remote_t client;
    auto operator<=>(const notify_t&) const = default;
};

struct detach_t
{
    remote_t client;
    auto operator<=>(const detach_t&) const = default;
};

using action_t = std::variant<
    acquire_t,
    release_t,
    detach_t
>;

using rxqueue_t = bln_queue::msg_queue<action_t>;
using txqueue_t = bln_queue::msg_queue<notify_t>;

} // namespace sema
