#include <winsock2.h>						// Windows Sockets 2 header
#include <ws2tcpip.h>						// IP Helper API header
#include <iostream>	
#pragma comment(lib, "ws2_32.lib")			// Link with ws2_32.lib

int main() {
	/* 初始化 Winsock */
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
	/* 创建套接字 */
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }
	/* 设置服务器地址结构 */
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	/* 连接到服务器 */
    if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connect failed\n";
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server!\n";
	/* 发送数据 */
    send(sock, "Hello from client!", 18, 0);
	/* 接收数据 */
    char buffer[512];
    int bytesReceived = recv(sock, buffer, sizeof(buffer)-1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received from server: " << buffer << "\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
