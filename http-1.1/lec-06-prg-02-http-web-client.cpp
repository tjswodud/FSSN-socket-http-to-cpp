#include <boost/asio.hpp>
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

int main()
{
    boost::system::error_code ec;
    std::cout << "## HTTP client started." << std::endl;
    std::cout << "## GET request for http://localhost:8080/temp/" << std::endl;
    
    net::io_service svc;
    tcp::socket sock(svc);
    sock.connect({{}, 8080});

    std::string request("GET /temp/temp");
    sock.send(net::buffer(request));

    std::string response;

    do
    {
        char buf[1024];
        size_t bytes_transferred = sock.receive(net::buffer(buf), {}, ec);
        if (!ec)
        {
            response.append(buf, buf + bytes_transferred);
        }
    } while (!ec);
    
    std::cout << "## GET response [start]" << std::endl;
    std::cout << response << std::endl;
    std::cout << "## GET response [end]" << std::endl;

    std::cout << "## GET request for http://localhost:8080/?var1=9&var2=9" << std::endl;
    sock.send(net::buffer(request));
    std::cout << "## GET response [start]" << std::endl;
    std::cout << response << std::endl;
    std::cout << "## GET response [end]" << std::endl;
    
    std::cout << "## POST request for http://localhost:8080/ with var1 is 9 and var2 is 9" << std::endl;
    sock.send(net::buffer(request));
    std::cout << "## GET response [start]" << std::endl;
    std::cout << response << std::endl;
    std::cout << "## GET response [end]" << std::endl;
    
    std::cout << "## HTTP client completed." << std::endl;
}