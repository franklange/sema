#include <sema/client.h>
#include <sema/protocol.h>

namespace sema {

client::client(socket_t& s, remote_t r)
    : m_socket{s}
    , m_server{std::move(r)}
{}

void client::acquire()
{
    m_socket.put(to_packet(acquire_t{m_server}));
    m_socket.wait();
}

void client::release()
{
    m_socket.put(to_packet(release_t{m_server}));
}

} // namespace sema
