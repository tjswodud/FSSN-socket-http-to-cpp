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

using namespace std::chrono_literals;

int currentThread = 0;

void ThreadedTCPServer(int clientSock, char* recvBuff, char* sendBuff)
{
    while (true)
    {
        recv(clientSock, recvBuff, 1024, 0);
        strcpy(sendBuff, recvBuff);
        std::cout << "> echoed: " << recvBuff << " by " << std::this_thread::get_id() << std::endl;
        send(clientSock, sendBuff, strlen(sendBuff) + 1, 0);

        if (strcmp(recvBuff, "quit") == 0)
        {
            break;
        }
    }
}

int main()
{
    char msg[2048];

    std::cout << "> echo-server is activated" << std::endl;
    currentThread++;

    std::string HOST = "localhost";
    unsigned int PORT = 65456;

    int serverSocket, clientSocket, c;
    int opt = 1;
    struct sockaddr_in server, client;
    char recvBuffer[1024], sendBuffer[1024];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

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
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "> bind() failed by exception: " << e.what() << std::endl;
        close(serverSocket);
        return 0;
    }

    if (listen(serverSocket, 3) == -1)
    {
        std::cout << "> listen() failed and program terminated" << std::endl;
        close(serverSocket);
        return 0;
    }

    clientSocket = accept(serverSocket, (struct sockaddr*)& client, (socklen_t*)& c);

    std::cout << "> client connected by IP address " << HOST << " with Port number " << client.sin_port << std::endl;

    std::thread serverThread(ThreadedTCPServer, clientSocket, recvBuffer, sendBuffer);
    serverThread.detach();
    serverThread.native_handle();
    std::cout << "> server loop running in thread (main thread): " << std::this_thread::get_id() << std::endl;

    int baseThreadNumber = currentThread;
    while (true)
    {
        std::cout << "> ";
        std::cin >> msg;

        if (strcmp(msg, "quit") == 0)
        {
            if (baseThreadNumber == currentThread)
            {
                std::cout << "> stop procedure started" << std::endl;
                break;
            }
            else
            {
                std::cout << "> active threads are remained : " << baseThreadNumber << " threads" << std::endl;
            }
        }
    }

    std::cout << "> echo server is de-activated" << std::endl;
}