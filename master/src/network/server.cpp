#include "server.hpp"
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "error.hpp"

void Server::Initialize() {
    int opt = 1;
    ssize_t valread;

    if ((serverFd = socket(domain, SOCK_STREAM, 0)) < 0) {
        throw Error{"socket failed"};
    }

    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        throw Error{"setsockopt failed"};
    }
 
    if (bind(serverFd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw Error{"bind failed"};
    }

    if (listen(serverFd, 3) < 0) {
        throw Error{"listen failed"};
    }
}

void Server::Loop() {
    while(true) {   
        FD_ZERO(&readFds);   
     
        FD_SET(serverFd, &readFds);   
        
        wait();
             
        if (FD_ISSET(serverFd, &readFds)) {   
            connectionRequest();
        }   
             
        for (int i=0;i<numberClients;i++) {   
            int clientFd = clientSockets[i];   
                 
            if (FD_ISSET(clientFd , &readFds)) {    
                readSocket(clientFd, i);
            }   
        }   
    }  
}

void Server::wait() {
    int maxFdNumber = serverFd;   
             
    for (int i=0;i<numberClients;i++) {   
        int clientFd = clientSockets[i];   
                
        if(clientFd > 0) {
            FD_SET( clientFd , &readFds);   
        } 
        
        if(clientFd > maxFdNumber) {
            maxFdNumber = clientFd;   
        }
    }   
    
    int activity = select( maxFdNumber + 1 , &readFds , NULL , NULL , NULL);   
    
    if (activity < 0 && errno!=EINTR) {   
        throw Error{"select failed"}; 
    } 
}

void Server::readSocket(int clientFd, int index) {
    int valRead;
    char buffer[1025];

    if ((valRead = read(clientFd , buffer, 1024)) == 0) {   
        getpeername(clientFd , (struct sockaddr*)&address , (socklen_t*)&addrlen);   
        
        printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));   
                
        close(clientFd);   
        clientSockets[index] = 0;   
    } else {   
        buffer[valRead] = '\0';   
        send(clientFd , buffer , strlen(buffer) , 0);   
    }
}

void Server::connectionRequest() {
    int newSocket;
            
    if ((newSocket = accept(serverFd, (struct sockaddr*)&address, &addrlen)) < 0) {
        throw Error{"accept failed"};
    }
        
    printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSocket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));   

    bool full = true;

    for (int i=0;i<numberClients;i++) {  
        if(clientSockets[i] == 0) {
            full = false;
            clientSockets[i] = newSocket;   
            printf("Adding to list of sockets as %d\n" , i);   
                    
            break;   
        } 
    }

    if (full) {
        getpeername(newSocket , (struct sockaddr*)&address , (socklen_t*)&addrlen);   
        close(newSocket);
            
        printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
    }
}

void Server::Close() {
    close(serverFd);

    for (int i=0;i<numberClients;i++) {
        if (clientSockets[i] != 0) {
            close(clientSockets[i]);
        }
    }
}
