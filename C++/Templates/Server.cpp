/**
 * @file main.cpp
 * @brief GUI程序入口
 *
 */

#include <winsock2.h>						// Socket API header
#include <ws2tcpip.h>						// IP Helper API header
#include <iostream>
#pragma comment(lib, "ws2_32.lib")			// link Winsock Library

int main() {
	/* 初始化 Winsock */
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }
	/* 创建监听套接字 */
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        WSACleanup();
        return 1;
    }
	/* 绑定并监听 */
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // 监听所有网卡
    serverAddr.sin_port = htons(8888);       // 端口 8888
	
    if (bind(listenSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }
	/* 开始监听 */
    if (listen(listenSock, 5) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Server listening on port 8888...\n";
	/* 接受客户端连接 */
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);
	// 阻塞等待客户端连接
    SOCKET clientSock = accept(listenSock, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(listenSock);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected!\n";
	/* 处理客户端请求 */
    char buffer[512];
    int bytesReceived = recv(clientSock, buffer, sizeof(buffer)-1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Received from client: " << buffer << "\n";
        send(clientSock, "Hello from server!", 18, 0);
    }
	/* 清理 */
    closesocket(clientSock);
    closesocket(listenSock);
    WSACleanup();
    return 0;
}
