#include <iostream>
#include "server.hpp"
#include "error.hpp"

#define PORT 8080

int main(int argc, char const* argv[])
{
    Server* s = new Server{PORT, AF_INET, 3};

    try {
        s->Initialize();
        s->Loop();
        s->Close();
    } catch (Error e) {
        std::cout << e.message << std::endl;
    }
    
    return 0;
}
