#include <cstdlib>
#include <cstring>
#include <iostream>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>

int main(int argc, char* argv[])
{
    std::string HOST = "127.0.0.1";
    unsigned int PORT = 65456;

    int client_sock, c;
    struct sockaddr_in server, client;

    char* sendMsg;
    ssize_t recvData;
    char sendBuffer[2048];
    char recvBuffer[2048];

    std::cout << "> echo-client is activated" << std::endl;

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    connect(clientSocket, (struct sockaddr*)& server, sizeof(server));
    
    while (true)
    {
        std::cout << "> ";
        std::cin >> sendBuffer;
        send(clientSocket, sendBuffer, strlen(sendBuffer) + 1, 0);
        recv(clientSocket, recvBuffer, 1024, 0);
        std::cout << "> received: " << recvBuffer << std::endl;
        if (strcmp(sendBuffer, "quit") == 0)
            break;
    }
}