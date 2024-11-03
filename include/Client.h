#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <arpa/inet.h>
#include <nlohmann/json.hpp>

#pragma comment(lib, "ws2_32.lib")

class Client {
private:
    int sock;
    struct sockaddr_in server;

public:
    Client();
    void connect_Server(const std::string &server_address, int port);
    void close_Connection();
    void send_Data(const nlohmann::json &data);
    nlohmann::json receive_Data();
    void show_Menu();
};

#endif // CLIENT_H