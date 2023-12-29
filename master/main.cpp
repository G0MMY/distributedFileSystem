#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
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
    

    // int server_fd, new_socket;
    // ssize_t valread;
    // struct sockaddr_in address;
    
    // socklen_t addrlen = sizeof(address);
    // char buffer[1024] = { 0 };
    // char* hello = "Hello from server";
 
    // // Creating socket file descriptor
    // if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    //     perror("socket failed");
    //     exit(EXIT_FAILURE);
    // }
 
    // // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET,
    //                SO_REUSEADDR | SO_REUSEPORT, &opt,
    //                sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(PORT);
 
    // // Forcefully attaching socket to the port 8080
    // if (bind(server_fd, (struct sockaddr*)&address,
    //          sizeof(address))
    //     < 0) {
    //     perror("bind failed");
    //     exit(EXIT_FAILURE);
    // }
    // if (listen(server_fd, 3) < 0) {
    //     perror("listen");
    //     exit(EXIT_FAILURE);
    // }
    // if ((new_socket
    //      = accept(server_fd, (struct sockaddr*)&address,
    //               &addrlen))
    //     < 0) {
    //     perror("accept");
    //     exit(EXIT_FAILURE);
    // }
    // valread = read(new_socket, buffer,
    //                1024 - 1); // subtract 1 for the null
    //                           // terminator at the end
    // printf("%s\n", buffer);
    // send(new_socket, hello, strlen(hello), 0);
    // printf("Hello message sent\n");
 
    // // closing the connected socket
    // close(new_socket);
    // // closing the listening socket
    // close(server_fd);
    return 0;
}