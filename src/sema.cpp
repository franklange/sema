#include <sema/log.h>
#include <sema/sema.h>

#include <algorithm>

namespace sema {

namespace {

auto has(const remotes_t& rs, const remote_t& r) -> bool
{
    return (std::find(rs.begin(), rs.end(), r) != rs.end());
}

auto rm(remotes_t& rs, const remote_t& r)
{
    return rs.erase(std::remove(rs.begin(), rs.end(), r));
}

} // namespace anonym

sema_t::sema_t(rxqueue_t& rx, txqueue_t& tx, const unsigned count)
    : m_rx{rx}
    , m_tx{tx}
    , m_state{count}
{}

void sema_t::process()
{
    std::visit(*this, m_rx.wait());
}

void sema_t::operator()(acquire_t a)
{
    if (has(m_state.holders, a.client))
    {
        sema_dbg("[sema] [a] [err] already a holder:", a.client.to_string());
        return;
    }

    if (has(m_state.waiters, a.client))
    {
        sema_dbg("[sema] [a] [err] already a waiter:", a.client.to_string());
        return;
    }

    if (!m_state.count)
    {
        sema_dbg("[sema] [a] add waiter:", a.client.to_string());
        m_state.waiters.push_back(std::move(a.client));
        return;
    }

    m_state.count--;
    m_state.holders.push_back(a.client);

    sema_dbg("[sema] [a] add holder:", a.client.to_string());
    sema_dbg("[sema] [a] count:", m_state.count, "hs:", m_state.holders.size(), "ws:", m_state.waiters.size());

    m_tx.put({std::move(a.client)});
    sema_dbg("[sema] [a] sent notify");

    return;
}

void sema_t::operator()(const release_t& a)
{
    if (!has(m_state.holders, a.client))
    {
        sema_dbg("[sema] [r] [err] not a holder:", a.client.to_string());
        return;
    }

    if (has(m_state.waiters, a.client))
    {
        sema_dbg("[sema] [r] [err] only a waiter:", a.client.to_string());
        return;
    }

    m_state.count++;
    rm(m_state.holders, a.client);

    sema_dbg("[sema] [r] del holder:", a.client.to_string());

    if (m_state.waiters.empty())
        return;

    remote_t w = m_state.waiters.front();
    sema_dbg("[sema] [r] mov waiter:", w.to_string());

    rm(m_state.waiters, w);
    (*this)(acquire_t{std::move(w)});

    return;
}

void sema_t::operator()(const detach_t& a)
{
    if (has(m_state.holders, a.client))
    {
        sema_dbg("[sema] [d] del holder:", a.client.to_string());
        (*this)(release_t{a.client});

        return;
    }

    if (has(m_state.waiters, a.client))
    {
        rm(m_state.waiters, a.client);
        sema_dbg("[sema] [d] del waiter:", a.client.to_string());

        return;
    }

    sema_dbg("[sema] [d] unknown:", a.client.to_string());
    return;
}

} // namespace sema
