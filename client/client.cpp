#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include"cJSON.h"
#include <unistd.h>

#define OFFLINE 0
#define READY 1
#define MOVING 2

cJSON * request(const int sock, cJSON *root)
{

    char *json_str = cJSON_Print(root);

    // 发送JSON数据包请求
    std::cout << "Sending request..." << std::endl;
    send(sock, json_str, strlen(json_str), 0);
    
    // 释放内存
    cJSON_Delete(root);
    free(json_str);

    // 等待服务器响应
    std::cout << "Waiting for server response..." << std::endl;
    char buffer[1024];
    read(sock, buffer, 1024);
    printf("Server response: \n");

    // 解析服务器响应中的JSON数据
    return cJSON_Parse(buffer);

}


int main() {
    // Server 的 IP 和 Port
    const char* host = "127.0.0.1"; 
    const int port = 12345;

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // 连接服务器，直到回复
    int cnt = 10;
    while(cnt--){
        sockaddr_in server_address;
        memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        inet_pton(AF_INET, host, &server_address.sin_addr); 
        if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) == 0) {
            std::cout << "Connect Server Success!" << std::endl;
            break;
        }
        std::cout << "Connecting to server..." << std::endl;        
        sleep(1);
    }

    // 创建JSON对象
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "Device", "DualArm"); // 设备名称
    cJSON_AddNumberToObject(root, "State", MOVING); // 设备状态

    // 发送请求，等待响应
    cJSON *response = request(client_socket, root);
    
    // 解析响应
    printf("TimeStamps: %f\n", cJSON_GetObjectItem(response, "TimeStamps")->valuedouble);
    printf("Command: %d\n", cJSON_GetObjectItem(response, "Command")->valueint);    
    
    // 关闭套接字
    close(client_socket);

    return 0;
}
