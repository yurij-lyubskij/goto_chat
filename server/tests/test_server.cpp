#include <gtest/gtest.h>

#include "Server.h"

TEST(Server, ParseRequest) {
    Server server;
    std::string rawRequest = "GET /server/chat HTTP/1.1\n"
                             "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\n"
                             "Host: www.ourserver.com\n"
                             "Accept-Language: en-us\n"
                             "Accept-Encoding: gzip, deflate\n"
                             "Connection: Keep-Alive";
    Request request = server.ParseRequest(rawRequest);
    EXPECT_EQ(request.method, "GET");
}

TEST(Server, Serialise) {
    Server server;
    std::string responseRaw = "HTTP/1.1 200 OK\n"
                              "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                              "Server: Apache/2.2.14 (Win32)\n"
                              "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                              "Content-Length: 88\n"
                              "Content-Type: text/html\n"
                              "Connection: Keep-Alive"
                              "<html>\n"
                              "<body>\n"
                              "<h1>Hello, World!</h1>\n"
                              "</body>\n"
                              "</html>";
    Response response;
    response.statusCode = 200;
    response.headers = {"Date: Mon, 27 Jul 2009 12:28:53 GMT\n",
                        "Server: Apache/2.2.14 (Win32)\n",
                        "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n",
                        "Content-Length: 88\n",
                        "Content-Type: text/html\n",
                        "Connection: Keep-Alive"};

    response.body = "<html>\n"
                    "<body>\n"
                    "<h1>Hello, World!</h1>\n"
                    "</body>\n"
                    "</html>";

    std::string serialized = server.Serialise(response);
    EXPECT_EQ(responseRaw, serialized);
}
