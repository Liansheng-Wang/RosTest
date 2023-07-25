#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <thread>
#include <vector>


const int MAX_FRAME_SIZE = 1024;
const char FRAME_DELIMITER = '\n';
const int MAX_CLIENTS = 3;                 // 最大客户端数（三架无人机）
const char ServerIP[] = "192.168.31.5";
const int PORT = 18833;


class UavTCPServer{
public:
	UavTCPServer(){}
	~UavTCPServer(){
		close(server_socket_);
	}

	bool init(){
		server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
		if (server_socket_ == -1) {
			std::cerr << "Error creating socket" << std::endl;
			return false;
		}
		server_addr_.sin_family = AF_INET;
		server_addr_.sin_port = htons(PORT);
		server_addr_.sin_addr.s_addr = inet_addr(ServerIP);
		if (bind(server_socket_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) == -1) {
			std::cerr << "Error binding socket" << std::endl;
			close(server_socket_);
			return false;
		}
	}

	void run_listen(){
		if (listen(server_socket_, 3) == -1) {
			std::cerr << "Error listening to socket" << std::endl;
			close(server_socket_);
			return;
		}

		// 等待客户端连接
		while (true) {
			sockaddr_in client_addr;
			socklen_t client_addr_size = sizeof(client_addr);
			int client_socket = accept(server_socket_, (struct sockaddr *)&client_addr, &client_addr_size);
			if (client_socket == -1) {
				std::cerr << "Error accepting client connection" << std::endl;
				close(server_socket_);
				return;
			}

			// 为新的客户端连接创建一个独立的线程来处理
			std::thread client_thread(handleClient, client_socket);
			client_thread.detach(); // 独立运行，不阻塞主线程
		}
	}

private:
	void handleClient(int client_socket){
		char buffer[MAX_FRAME_SIZE];
		std::string current_frame;
		while (true) {
			ssize_t recv_size = recv(client_socket, buffer, sizeof(buffer), 0);
			if (recv_size == -1) {
				std::cerr << "Error receiving data from client" << std::endl;
				break;
			} else if (recv_size == 0) {
				std::cout << "Client disconnected" << std::endl;
				break;
			}

			// 将接收到的数据加入当前帧
			current_frame.append(buffer, recv_size);

			// 查找分隔符，切分出完整的数据帧
			size_t pos;
			while ((pos = current_frame.find(FRAME_DELIMITER)) != std::string::npos) {
				std::string data_frame = current_frame.substr(0, pos);
				current_frame.erase(0, pos + 1);


				std::cout << "Received data frame from client " << client_socket << ": " << data_frame << std::endl;
			}
		}

		close(client_socket);
	}

public:
	int server_socket_;
	sockaddr_in server_addr_;
	std::vector<std::thread> clients_;
};


int main() {
  UavTCPServer uav_tcp_ser;
	if(uav_tcp_ser.init()){
		uav_tcp_ser.run_listen();
	}
  return 0;
}
