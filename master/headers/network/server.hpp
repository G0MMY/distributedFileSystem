#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

class Server {
    int port, domain, numberClients, serverFd;
    int* clientSockets;
    fd_set readFds;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);

public:
    Server(int port, int domain, int numberClients): port{port}, domain{domain}, numberClients{numberClients} {
        clientSockets = new int[numberClients];
        
        address.sin_family = domain;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port);
    };

    ~Server() {
        Close();
        delete(clientSockets);
    }

    void Initialize();
  
    void Loop();
    void Close();

private:
    void wait();
    void connectionRequest();
    void readSocket(int clientFd, int index);
};

#endif