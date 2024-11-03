#include <Client.h>


using json = nlohmann::json;

Client::Client() : sock(-1) {} // Initialize socket to -1

void Client::connect_Server(const std::string &server_address, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0); // Create a socket
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if(inet_pton(AF_INET, server_address.c_str(), &server.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
}

void Client::close_Connection() {
    close(sock); // Close the socket
}

void Client::send_Data(const json &data) {
    std::string data_str = data.dump();
    send(sock, data_str.c_str(), data_str.size(), 0);
}

json Client::receive_Data() {
    char buffer[1024] = {0};
    int valread = read(sock, buffer, 1024);
    return json::parse(std::string(buffer, valread)); // Parse string to JSON
}

void Client::show_Menu() {
    std::string server_address;
    int port;

    // Prompt user for server address and port
    std::cout << "Enter server IP address: ";
    std::cin >> server_address;
    std::cout << "Enter server port: ";
    std::cin >> port;

    connect_Server(server_address, port); // Connect to the server

    json message; // JSON object to hold message
    while (true) {
        std::cout << "Enter message to send (or 'exit' to quit): ";
        std::string input;
        std::cin >> input; // Get input from user
        if (input == "exit") {
            break; // Exit the loop if user types 'exit'
        }

        message["message"] = input;  // Create JSON message with user input
        send_Data(message); // Send JSON data to server

        json response = receive_Data(); // Receive response from server
        std::cout << "Response from server: " << response.dump() << std::endl;  // Display response
    }
    close_Connection(); // Close the connection
}