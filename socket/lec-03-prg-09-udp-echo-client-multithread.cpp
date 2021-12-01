#include <cstdlib>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <thread>
#include <vector>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

void RecvHandler(int clientSock)
{
    char recvBuffer[2048];
    
    while (true)
    {
        recv(clientSock, recvBuffer, 1024, 0);
        std::cout << "> received: " << recvBuffer << std::endl;
        if (strcmp(recvBuffer, "quit") == 0)
            break;
    }
}

void MainThread()
{
    std::string HOST = "127.0.0.1";
    unsigned int PORT = 65456;

    int client_sock, c;
    struct sockaddr_in server, client;
    char sendBuffer[2048];
    
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    try
    {
        if (connect(clientSocket, (struct sockaddr*)& server, sizeof(server)) == -1)
        {
            std::cout << "> connect() failed and program terminated" << std::endl;
            close(clientSocket);
            return;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "> connect() failed by exception: " << e.what() << std::endl;
        return;
    }

    std::thread clientThread = std::thread(RecvHandler, clientSocket);
    clientThread.native_handle();

    while (true)
    {
        std::cout << "> ";
        std::cin >> sendBuffer;
        send(clientSocket, sendBuffer, strlen(sendBuffer) + 1, 0);
        if (strcmp(sendBuffer, "quit") == 0)
            break;
    }
}

int main()
{
    std::cout << "> echo-client is activated" << std::endl;
    MainThread();
    std::cout << "> echo-client is de-activated" << std::endl;
}