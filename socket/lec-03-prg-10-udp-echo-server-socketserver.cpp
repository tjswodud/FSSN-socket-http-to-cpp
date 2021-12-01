#include <chrono>
#include <cstdlib>
#include <cstring>
#include <future>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void MyUDPServer(std::string host, unsigned int port)
{
    int serverSocket, clientSocket, c;
    int opt = 1;
    struct sockaddr_in server, client;
    char recvBuffer[1024], sendBuffer[1024];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    try
    {
        if (bind(serverSocket, (struct sockaddr*)& server, sizeof(server)) == -1)
        {
            std::cout << "> bind() failed and program terminated" << std::endl;
            close(serverSocket);
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "> bind() failed by exception: " << e.what() << std::endl;
        close(serverSocket);
        return;
    }

    if (listen(serverSocket, 3) == -1)
    {
        std::cout << "> listen() failed and program terminated" << std::endl;
        close(serverSocket);
        return;
    }

    clientSocket = accept(serverSocket, (struct sockaddr*)& client, (socklen_t*)& c);

    while (true)
    {
        recv(clientSocket, recvBuffer, 1024, 0);
        strcpy(sendBuffer, recvBuffer);
        std::cout << "> echoed: " << recvBuffer << std::endl;
        send(clientSocket, sendBuffer, strlen(sendBuffer) + 1, 0);
        if (strcmp(recvBuffer, "quit") == 0)
            break;
    }
}

int main()
{
    std::string HOST = "127.0.0.1";
    unsigned int PORT = 65456;

    std::cout << "> echo-server is activated" << std::endl;
    MyUDPServer(HOST, PORT);
    std::cout << "> echo-server is de-activated" << std::endl;
}