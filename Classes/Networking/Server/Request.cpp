//
// Created by Maykon Meneghel on 21/04/22.
//

#include "Request.h"
#include "HttpServer.h"

Request::Request(HttpServer& server): server(server)
{
    socket.reset(new tcp::socket(this->server.io_service));
}

std::string Request::make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

void Request::afterRead(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    boost::asio::streambuf response;
    std::ostream res_stream(&response);

    std::string time = make_daytime_string();

    if(server.ReadAuth(request))
    {
        std::ifstream html(Paths::SuccessHTML);
        html.seekg(0, std::ios::end);
        size_t size = html.tellg();
        std::string buffer(size, ' ');
        html.seekg(0);
        html.read(&buffer[0], size);

        res_stream << "HTTP/1.0 200 OK\r\n"
                   << "Content-Type: text/html\r\n"
                   << "Content-Length: " << size << "\r\n\r\n"
                   << buffer << "\r\n";

    } else
    {
        std::ifstream html(Paths::FailHTML);
        html.seekg(0, std::ios::end);
        size_t size = html.tellg();
        std::string buffer(size, ' ');
        html.seekg(0);
        html.read(&buffer[0], size);

        std::string message = "Bad Request";
        res_stream << "HTTP/1.0 403 Bad Request\r\n"
                   << "Content-Type: text/html; charset=UTF-8\r\n"
                   << "Content-Length: " << size << "\r\n\r\n"
                   << buffer << "\r\n";
    }

    boost::asio::async_write(*socket, response, boost::bind(&Request::afterWrite, shared_from_this(), boost::system::error_code(), std::size_t(2048)));

}

void Request::afterWrite( const boost::system::error_code& ec, std::size_t bytes_transferred) const
{
    socket->close();
}

void Request::answer()
{
    if (!socket) return;
    boost::asio::async_read_until(*socket, request, "\r\n\r\n", boost::bind(&Request::afterRead, shared_from_this(), boost::system::error_code(), std::size_t(2048)));
}