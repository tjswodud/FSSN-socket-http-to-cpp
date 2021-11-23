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
    std::string PORT_S(std::to_string(PORT));

    int clientSocket, c;
    int opt = 1;
    struct sockaddr_in server, client;

    char buffer[1024], recvData[1024];
    char* recvMsg;

    std::cout << "> echo-server is activated" << std::endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    bind(serverSocket, (struct sockaddr*)& server, sizeof(server));
    listen(serverSocket, 3);

    clientSocket = accept(serverSocket, (struct sockaddr*)& client, (socklen_t*)& c);

    std::cout << "> client connected by IP address " << HOST << " with Port number " << PORT_S << std::endl;
    while (true)
    {
        recv(clientSocket, buffer, 1024, 0);
        strcpy(recvData, buffer);
        send(clientSocket, recvData, strlen(recvData) + 1, 0);
        std::cout << "> echoed: " << buffer << std::endl;
        if (strcmp(buffer, "quit") == 0)
        {
            std::cout << "> echo-server is de-activated" << std::endl;
            break;
        }
    }
}