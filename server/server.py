import socket
import json
import time

host = '0.0.0.0'
port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)  # 允许多个客户端连接

print(f"等待连接在 {host}:{port}")

while True:
    client_socket, client_address = server_socket.accept()
    print(f"连接来自 {client_address}")

    while True:
        data = client_socket.recv(1024)
        if not data:
            break  # 客户端断开连接
        print(f"接收到数据: {data.decode()}")

        # 在这里进行回复
        # 将字典转换为JSON字符串
        response = json.dumps(
            {
                "TimeStamps": time.time(),
                "Command": 7, 
            }
        )
        # 发送响应
        client_socket.send(response.encode())

    client_socket.close()

  
