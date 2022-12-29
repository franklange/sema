#pragma once

#include <sema/types.h>

namespace sema {

struct state_t
{
    unsigned count{0};

    remotes_t holders{};
    remotes_t waiters{};

    auto operator<=>(const state_t&) const = default;
};

} // namespace sema
