import socket
import json
import time

host = '0.0.0.0' # 允许任何IP地址连接
port = 12345

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((host, port))
server_socket.listen(5)  # 允许多个客户端连接

print(f"监听 Port: {port}")

while True:

    server_socket.settimeout(1) # 设置超时时间
    while True:
        try:
            client_socket, client_address = server_socket.accept()
            break
        except socket.timeout:
            continue
    

    while True:
        data = client_socket.recv(1024)
        if not data:
            break  # 客户端断开连接

        try:
            decoded_data = json.loads(data.decode())
        except json.JSONDecodeError:
            print("非JSON数据")
            break
        
        print(f"连接来自 {client_address} 设备名称： " + decoded_data["Device"])

        # 在这里进行回复

        if(decoded_data["Device"] == "Dual Arm Robot"): # 双臂机器人
            RobotState = decoded_data["State"]
            print(f"双臂机器人状态: {RobotState}")
            response = json.dumps({
                    "TimeStamps": time.time(), # 时间戳
                    "Command": 7, # 命令的编号
                })
        if(decoded_data["Device"] == "Raspberry Pi"): # 树莓派
            RspState = decoded_data["State"]
            response = json.dumps({
                    "TimeStamps": time.time(), # 时间戳
                    "Command": 7, # 命令的编号
                })
        else: # 未知设备
            response = json.dumps({
                    "TimeStamps": time.time(), # 时间戳
                    "Message": "Access Denied.", 
                })

        client_socket.send(response.encode())

    client_socket.close()

  
