# FILEPATH: /Users/uneypan/Desktop/SocketExample/client/client.py
import socket
import json

def request(sock, data):
    # 将数据转换为JSON字符串
    json_str = json.dumps(data)

    # 发送JSON数据包请求
    print("Sending request...")
    sock.sendall(json_str.encode())

    # 等待服务器响应
    print("Waiting for server response...")
    buffer = sock.recv(1024).decode()
    print("Server response: ")
    print(buffer)

    # 解析服务器响应中的JSON数据
    return json.loads(buffer)


if __name__ == "__main__":
    # Server 的 IP 和 Port
    host = "127.0.0.1"
    port = 12345

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
        server_address = (host, port)
        print("Connecting to server...")
        client_socket.connect(server_address)
        print("Connect Server Success!")

        # 创建JSON对象
        data = {
            "Device": "Dual Arm Robot",  # 设备名称
            "State": "Ready"  # 设备状态
        }

        # 发送请求，等待响应
        response = request(client_socket, data)

        # 解析响应
        print("TimeStamps: ", response["TimeStamps"])
        print("Command: ", response["Command"])

    # 关闭套接字
    client_socket.close()
