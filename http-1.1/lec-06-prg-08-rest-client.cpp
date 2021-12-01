#include <iostream>
#include <cpprest/http_listener.h>

using namespace web::http;
using namespace web::http::experimental::listener;

int main()
{
    http_request request;
    http_response response;
    std::cout << "#1 Code: " << response.status_code()<< ">> JSON: ";

    request.extract_json(false);
    std::cout << "#1 Code: " << response.status_code()<< ">> JSON: ";
    std::cout << "#1 Code: " << response.status_code()<< ">> JSON: ";
    std::cout << "#1 Code: " << response.status_code()<< ">> JSON: ";
}