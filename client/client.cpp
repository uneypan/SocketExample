#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const char* host = "127.0.0.1"; // Server_IP
    const int port = 12345;

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, host, &server_address.sin_addr);

    connect(client_socket, (sockaddr*)&server_address, sizeof(server_address));

    while (true) {
        std::string data_to_send;
        std::cout << "输入要发送的数据 (输入 'exit' 退出): ";
        std::getline(std::cin, data_to_send);
        if (data_to_send == "exit") {
            break;
        }

        send(client_socket, data_to_send.c_str(), data_to_send.size(), 0);

        char response[1024] = {0};
        recv(client_socket, response, sizeof(response), 0);
        std::cout << "服务器响应: " << response << std::endl;
    }

    close(client_socket);

    return 0;
}
