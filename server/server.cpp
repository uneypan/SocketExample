#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    const char* host = "0.0.0.0";
    const int port = 12345;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "创建套接字失败" << std::endl;
        return 1;
    }

    sockaddr_in server_address;
    std::memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(host);
    server_address.sin_port = htons(port);

    if (bind(server_socket, (sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "绑定套接字失败" << std::endl;
        return 1;
    }

    if (listen(server_socket, 5) == -1) {
        std::cerr << "监听套接字失败" << std::endl;
        return 1;
    }

    std::cout << "等待连接在 " << host << ":" << port << std::endl;

    while (true) {
        sockaddr_in client_address;
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket == -1) {
            std::cerr << "接受连接失败" << std::endl;
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::cout << "连接来自 " << client_ip << ":" << ntohs(client_address.sin_port) << std::endl;

        while (true) {
            char buffer[1024] = {0};
            ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
            if (bytes_received == -1) {
                std::cerr << "接收数据失败" << std::endl;
                break;
            } else if (bytes_received == 0) {
                std::cout << "客户端断开连接" << std::endl;
                break;
            }

            std::cout << "接收到数据: " << buffer << std::endl;

            // 在这里处理数据，可以根据需要进行回复
            const char* response = "数据已收到！";
            send(client_socket, response, std::strlen(response), 0);
        }

        close(client_socket);
    }

    close(server_socket);
    return 0;
}