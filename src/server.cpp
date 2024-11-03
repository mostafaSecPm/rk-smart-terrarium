#include <Server.h>

using json = nlohmann::json;


Server::Server(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, int(&opt) , sizeof(opt))) {
        perror("Set socket options failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started, waiting for connections..." << std::endl;
    start_Accept(); // Start accepting client connections
}

void Server::start_Accept() {
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); // Accept a client connection
    if (new_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    handle_Client(); // Handle communication with the client
}

void Server::handle_Client() {
    while (true) {
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);

        if (valread <= 0) {
            std::cout << "Client disconnected." << std::endl;
            break; // Exit loop
        }

        json message = json::parse(std::string(buffer, valread));
        std::cout << "Received: " << message.dump() << std::endl;

        std::string response_message = "Received your message: " + message["message"].get<std::string>();
        json response = {{"response", response_message}};  // Create JSON response
        send(new_socket, response.dump().c_str(), response.dump().size(), 0);
    }
    close(new_socket); // Close the connection with the client
}