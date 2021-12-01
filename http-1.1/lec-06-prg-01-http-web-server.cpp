#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <iostream>
#include <cstdlib>
#include <cstring>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum class RequestType
{
    GET,
    POST
};

class HTTPServer
{
public:
    HTTPServer(std::string server_name, unsigned int port_num);
    void PrintHTTPRequestDetail();
    void SendHTTPResponseHeader();
    void GET();
    void POST();
    void LogMessage();
    void SimpleCalculate(int para1, int para2);
    void ParameterRetrieval(std::string msg);
private:
    std::string clientAddress;
    unsigned int clientPort;
    RequestType requestType;
};

HTTPServer::HTTPServer(std::string server_name, unsigned int port_num)
{
    clientAddress = server_name;
    clientPort = port_num;
}

void HTTPServer::PrintHTTPRequestDetail()
{
    std::cout << "::Client address   : " << clientAddress << std::endl;
    std::cout << "::Client port      : " << clientPort << std::endl;
    // std::cout << "::Request command  : " << requestType << std::endl;
}

int main(int argc, char** argv)
{
    std::string serverName = "localhost";
    unsigned int port = 8080;

    std::cout << "## HTTP server started at http://" << serverName << ":" << port << "." << std::endl;
    HTTPServer server(serverName, port);
    std::cout << "HTTP server stopped." << std::endl;
}