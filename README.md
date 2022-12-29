# Sema

Redis-like semaphore as a service.

### Dependencies
* bln_net

### Example client
```c++
#include <sema/client.h>
#include <sema/log.h>
#include <sema/types.h>

#include <cstdint>
#include <string>

auto main(int, char** argv) -> int
{
    sema::cli_sock_t socket{static_cast<std::uint16_t>(std::stoi(argv[1]))};
    sema::client c{socket, {"127.0.0.1", 8000}};

    std::string in;
    while (std::getline(std::cin, in))
    {
        if (in == "a")
        {
            c.acquire();
            sema_log("acquired");
        }
        else if (in == "r")
        {
            c.release();
            sema_log("released");
        }
    }

    return 0;
}
```

### Build & Run example
```bash
git clone --recursive https://github.com/franklange/sema.git
cd sema
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DSEMA_EXAMPLES=ON ..
cmake --build . -j

./bin/sema_service &
./bin/sema_client 9000
```