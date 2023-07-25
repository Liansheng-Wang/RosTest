#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <string>


using namespace std;

const int PORT = 18833;  // 服务器监听的端口号
const int MAX_CLIENTS = 3;  // 最大客户端数（三架无人机）
const char ServerIP[] = "192.168.31.5";

int main() {
  // 创建套接字
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
      std::cerr << "Error creating socket" << std::endl;
      return 1;
  }

  // 设置服务器地址和端口
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT); // 服务器端口号
  inet_pton(AF_INET, ServerIP, &(server_addr.sin_addr)); // 服务器IP地址

  // 连接到服务器
  if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    std::cerr << "Error connecting to server" << std::endl;
    close(client_socket);
    return 1;
  }

  // // 发送消息给服务器
  // const char *message = "Hello, server!";
  // if (send(client_socket, message, strlen(message), 0) == -1) {
  //   std::cerr << "Error sending message to server" << std::endl;
  //   close(client_socket);
  //   return 1;
  // }
  
  // 接收服务器发送的消息
  const int MAX_FRAME_SIZE = 1024;
  char buffer[MAX_FRAME_SIZE] = {0};
  int bytes_received = 0;
  int frame_size = 0;

  while (true) {
    // 接收数据长度字段
    ssize_t recv_size = recv(client_socket, buffer + bytes_received, sizeof(int) - bytes_received, 0);
    if (recv_size == -1) {
      std::cerr << "Error receiving message from server" << std::endl;
      break;
    } else if (recv_size == 0) {
      std::cout << "Connection closed by server" << std::endl;
      break;
    } else {
      bytes_received += recv_size;
      if (bytes_received == sizeof(int)) {
        // 读取数据长度
        frame_size = *reinterpret_cast<int*>(buffer);
        if (frame_size > MAX_FRAME_SIZE) {
          std::cerr << "Frame size exceeds maximum" << std::endl;
          break;
        }
        bytes_received = 0;
      }
    }

    // 接收数据内容
    recv_size = recv(client_socket, buffer + bytes_received, frame_size - bytes_received, 0);
    if (recv_size == -1) {
      std::cerr << "Error receiving message from server" << std::endl;
      break;
    } else if (recv_size == 0) {
      std::cout << "Connection closed by server" << std::endl;
      break;
    } else {
      bytes_received += recv_size;
      if (bytes_received == frame_size) {
        // 在这里对接收到的完整一帧数据进行处理
        // 可以将 buffer 强制转换为你所期望的数据类型，然后进行相应的解析和处理
        // 处理完一帧数据后，清空缓冲区，准备接收下一帧数据
        memset(buffer, 0, MAX_FRAME_SIZE);
        bytes_received = 0;
        frame_size = 0;
      }
    }
  }

  // 关闭套接字
  close(client_socket);

    return 0;
}
