import socket
import time

host = '192.168.1.112'
port = 12345

client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((host, port))

while True:
    data_to_send = input("输入要发送的数据 (输入 'exit' 退出): ")
    if data_to_send == 'exit':
        break
    
    client_socket.send(data_to_send.encode())

    response = client_socket.recv(1024)
    print(f"服务器响应: {response.decode()}")

client_socket.close()
