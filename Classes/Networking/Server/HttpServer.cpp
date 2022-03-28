//
// Created by Maykon Meneghel on 23/03/22.
//

#include "HttpServer.h"

HttpServer::HttpServer(Context* context, unsigned int port): acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {
    this->context = context;
}

void HttpServer::thread_main()
{
    // adds some work to the io_service
    start_accept();
    io_service.run();
}

void HttpServer::start_accept()
{
    boost::shared_ptr<Request> req (new Request(*this));
    acceptor.async_accept(*req->socket, boost::bind(&HttpServer::handle_accept, this, req, asio::error_code()));
}

void HttpServer::handle_accept(const boost::shared_ptr<Request>& req, const asio::error_code& error)
{
    if (!error) { req->answer(); }
    start_accept();
}

void HttpServer::Run() {
    sThread.reset(new asio::thread(boost::bind(&HttpServer::thread_main, this)));
}

void HttpServer::on_read_header(const std::string& line)
{
    std::stringstream ssHeader(line);
    std::string headerName;
    std::getline(ssHeader, headerName, ':');

    std::string value;
    std::getline(ssHeader, value);
    headers[headerName] = value;
}

Request::Request(HttpServer& server): server(server)
{
    socket.reset(new tcp::socket(this->server.io_service));
}

std::string Request::make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

void Request::afterRead( const asio::error_code& ec, std::size_t bytes_transferred)
{
    std::istream buffer(&request);
    std::string line;

    while (getline(buffer, line, '\n')) {
        if (line.empty() || line == "\r") {
            break;
        }
        server.on_read_header(line);
    }

    server.ReadAuth();

    asio::streambuf response;
    std::ostream res_stream(&response);

    std::string time = make_daytime_string();

    res_stream << "HTTP/1.0 200 OK\r\n"
               << "Content-Type: text/html; charset=UTF-8\r\n"
               << "Content-Length: " << time.length() + 13 << "\r\n\r\n"
               << time << "\r\n";

    asio::async_write(*socket, response, boost::bind(&Request::afterWrite, shared_from_this(), asio::error_code(), std::size_t(2048)));

}

void Request::afterWrite( const asio::error_code& ec, std::size_t bytes_transferred) const
{
    // done writing, closing connection
    socket->close();
}

void Request::answer()
{
    if (!socket) return;
    asio::async_read_until(*socket, request, "\r\n\r\n", boost::bind(&Request::afterRead, shared_from_this(), asio::error_code(), std::size_t(2048)));
}

void HttpServer::ReadAuth() {
    std::cout << headers["Cookie"] << std::endl;

    std::stringstream ssCookie(headers["Cookie"]);

    std::string cookie = ssCookie.str();
    size_t n_params = std::count(cookie.begin(), cookie.end(), 0x3d);
    std::cout << n_params << std::endl;

    std::map<std::string, std::string> params;
    for(int i=0; i<n_params; i++)
    {
        std::string key;
        std::getline(ssCookie, key, '=');

        std::string value;
        std::getline(ssCookie, value, (i==(n_params-1)) ? '\r' : ';' );

        params[key] = value;
    }

    context->_sentAuthentication = false;
    context->_startingAuthentication = false;
    context->_finishedAuthentication = true;

}

std::string HttpServer::urlDecode(const std::string& str) {
    std::string ret;
    char ch;
    int i, ii;
    for (i=0; i<str.length(); i++) {
        if (int(str[i])==37) {
            sscanf(str.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else {
            ret+=str[i];
        }
    }
    return(ret);
}