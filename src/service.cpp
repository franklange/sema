#include <sema/sema.h>
#include <sema/types.h>
#include <sema/protocol.h>

#include <thread>

auto main() -> int
{
    sema::srv_sock_t socket{8000};

    sema::rxqueue_t rxq;
    sema::txqueue_t txq;

    std::thread tx{[&](){
        while (true)
            socket.put(sema::to_packet(txq.wait()));
    }};

    std::thread rx{[&](){
        while (true)
            rxq.put(sema::from_packet(socket.wait()));
    }};

    sema::sema_t s{rxq, txq, 1};

    while (true)
        s.process();

    return 0;
}
