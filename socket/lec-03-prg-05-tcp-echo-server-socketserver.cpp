#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>

class MyTCPSocketHandler
{
public:
    MyTCPSocketHandler(std::string host, unsigned int port);
    void Handle();
private:
    std::vector<int> clientSockets;
    std::string host;
    unsigned int port;
    int serverSocket, clientSocket, c;
    int opt = 1;
    struct sockaddr_in server, client;
    char recvBuffer[1024], sendBuffer[1024];
    struct timeval tv;
    fd_set readfds;
};

MyTCPSocketHandler::MyTCPSocketHandler(std::string HOST, unsigned int PORT)
{
    host = HOST;
    port = PORT;

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
}

void MyTCPSocketHandler::Handle()
{
    clientSocket = accept(serverSocket, (struct sockaddr*)& client, (socklen_t*)& c);
    clientSockets.push_back(clientSocket);

    std::cout << "> client connected by IP address " << host << " with Port number " << client.sin_port << std::endl;
    
    while (true)
    {
        if (!clientSockets.empty())
        {
            int clientSock = clientSockets[0];

            recv(clientSock, recvBuffer, 1024, 0);
            strcpy(sendBuffer, recvBuffer);
            std::cout << "> echoed: " << recvBuffer << std::endl;
            send(clientSock, sendBuffer, strlen(sendBuffer) + 1, 0);

            if (strcmp(recvBuffer, "quit") == 0)
            {
                close(clientSock);
                clientSockets.pop_back();

                clientSocket = accept(serverSocket, (struct sockaddr*)& client, (socklen_t*)& c);
                clientSockets.push_back(clientSocket);
                std::cout << "> client connected by IP address " << host << " with Port number " << client.sin_port << std::endl;
            }
        }
        else
        {
            break;
        }
    }
}

int main()
{
    std::string HOST = "127.0.0.1";
    unsigned int PORT = 65456;

    std::cout << "> echo-server is activated" << std::endl;
    MyTCPSocketHandler tcpServer(HOST, PORT); // server activated
    tcpServer.Handle();
    std::cout << "> echo-server is de-activated" << std::endl;
}