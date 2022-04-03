//
// Created by Maykon Meneghel on 23/03/22.
//

#include "HttpServer.h"

HttpServer::HttpServer(Context* context, unsigned int port): context(context), acceptor(io_service, tcp::endpoint(tcp::v4(), port)) {}

void HttpServer::thread_main()
{
    start_accept();
    io_service.run();
}

void HttpServer::start_accept()
{
    boost::shared_ptr<Request> req (new Request(*this));
    acceptor.async_accept(*req->socket, boost::bind(&HttpServer::handle_accept, this, req, boost::system::error_code()));
}

void HttpServer::handle_accept(const boost::shared_ptr<Request>& req, const boost::system::error_code& error)
{
    if (!error) { req->answer(); } else {
        std::cout << "Error (line 26 HttpServer.cpp): " << error.message() << std::endl;
    }

    start_accept();
}

void HttpServer::Run() {
    sThread.reset(new std::thread(boost::bind(&HttpServer::thread_main, this)));
}

void HttpServer::Stop() {
    io_service.stop();
    acceptor.close();

    if (sThread) {
        sThread->detach();
    }
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

bool HttpServer::ReadAuth(boost::asio::streambuf& request) {

    std::istream buffer(&request);
    std::string line;

    while (getline(buffer, line, '\n')) {
        if (line.empty() || line == "\r") {
            break;
        }
        this->on_read_header(line);
    }

    std::stringstream ssCookie(headers["Cookie"]);

    std::string cookie = ssCookie.str();
    size_t n_params = std::count(cookie.begin(), cookie.end(), 0x3d);

//    std::map<std::string, std::string> params;
    rapidjson::Document params;
    params.SetObject();
    for(int i=0; i<n_params; i++)
    {
        std::string key;
        std::getline(ssCookie, key, '=');
        key.erase(remove(key.begin(), key.end(), ' '), key.end());

        std::string value;
        std::getline(ssCookie, value, (i==(n_params-1)) ? '\r' : ';' );
        value.erase(remove(value.begin(), value.end(), ' '), value.end());

        if(key=="user")
        {
            rapidjson::Document user_doc;
            user_doc.SetObject();
            BAJson::parse(urlDecode(value), user_doc);

            BAJson::set(params, key,  user_doc.GetObject());
        } else {
            BAJson::set(params, key, urlDecode(value));
        }


    }

    if (!params.HasMember("user")) {
        return false;
    }

    context->saveUser(params);

    context->_startingAuthentication = false;
    context->_sentAuthentication = false;

    return true;
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


void Request::afterRead(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
    boost::asio::streambuf response;
    std::ostream res_stream(&response);

    std::string time = make_daytime_string();

    if(server.ReadAuth(request))
    {
        std::fstream htmlFile;
        htmlFile.open("/Users/maykonmeneghel/Desktop/TheBrokeTeam/BrokerApp/Resources/Html/success.html", std::ios::in);
        if(!htmlFile){
            std::cout << "File cannot open!" << std::endl;
        }

        htmlFile.seekg(0, std::ios::end);
//        std::cout << htmlFile.tellg() << std::endl;
        res_stream << "HTTP/1.0 200 OK\r\n"
                   << "Content-Type: text/html\r\n"
                   << "Content-Length: " << std::int16_t(htmlFile.tellg()) << "\r\n\r\n"
                   << htmlFile.rdbuf() << "\r\n";

        std::cout << htmlFile.rdbuf() << std::endl;

    } else
    {
        std::string message = "Bad Request";
        res_stream << "HTTP/1.0 403 Bad Request\r\n"
                   << "Content-Type: text/html; charset=UTF-8\r\n"
                   << "Content-Length: " << message.length() + 2 << "\r\n\r\n"
                   << message << "\r\n";
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