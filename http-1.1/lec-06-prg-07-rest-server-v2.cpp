#include <iostream>
#include <cpprest/http_listener.h>

using namespace web::http;
using namespace web::http::experimental::listener;

int main()
{
    http_listener listener("http://localhost:8080");
    listener.open().then([&listener](){std::cout << (U("\n start!!\n"));}).wait();
    listener.support(methods::GET, [](http_request req) {
        req.reply(status_codes::OK, U("hello World!"));
    });

    while (true);
    listener.close();
}