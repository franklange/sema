#pragma once

#include <sema/actions.h>
#include <sema/state.h>
#include <sema/types.h>

namespace sema {

class sema_t
{
public:
    sema_t(rxqueue_t&, txqueue_t&, unsigned);

    void process();

    void operator()(acquire_t);
    void operator()(const release_t&);
    void operator()(const detach_t&);

private:
    rxqueue_t& m_rx;
    txqueue_t& m_tx;

    state_t m_state;
};

} // namespace sema
