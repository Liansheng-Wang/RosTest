'''
Author: [you name]
Date: 2023-07-17 20:23:58
LastEditors: [you name]
LastEditTime: 2023-07-17 21:11:31
Description: 
'''
from socket import *
# UDP客户端、创建一个服务器端的Socket
socket_server = socket(AF_INET, SOCK_DGRAM)

# 2、定义服务器端的ip地址和端口号，元组形式
host_port = ('10.6.204.19', 8080)

# 3、服务器端的Socket来绑定地址和端口,只有绑定了地址和端口，才能称为服务器的Socket
socket_server.bind(host_port)

# 4、接收客户端发送过来的数据,每次接收1kb的数据，如果一直没收到数据会阻塞
# 收到的每一个数据报，里面是一个元组，第一个值是数据内容，第二个值是源地址
data = socket_server.recvfrom(1024)

# 解码
print(data[0].decode('utf-8'))
print(data)

# 5、关闭套接字、释放资源
socket_server.close()
