#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <arpa/inet.h>
#include <nlohmann/json.hpp>

class Server {
private:
    int server_fd, new_socket{};
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);

public:
    Server(int port);
    void start_Accept();
    void handle_Client();
};

#endif // SERVER_H