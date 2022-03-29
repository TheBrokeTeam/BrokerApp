//
// Created by Maykon Meneghel on 23/03/22.
//

#ifndef BROKERAPP_HTTPSERVER_H
#define BROKERAPP_HTTPSERVER_H

#include <iostream>
#include <ostream>
#include <istream>
#include <ctime>
#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>
#include "../Classes/Contexts/Context.h"
#include <algorithm>

using boost::asio::ip::tcp;
class HttpServer;

class Request : public boost::enable_shared_from_this<Request>
{
    static std::string make_daytime_string();

    // member variables
    HttpServer& server;
    boost::asio::streambuf request;

    void afterRead( const boost::system::error_code& ec, std::size_t bytes_transferred);
    void afterWrite( const boost::system::error_code& ec, std::size_t bytes_transferred) const;

public:
    boost::shared_ptr<tcp::socket> socket;
    explicit Request(HttpServer& server);
    void answer();

};

class HttpServer
{
public:
    Context* context;
    explicit HttpServer(Context*, unsigned int);
    ~HttpServer() { if (sThread) sThread->join(); }
    void Run();
    boost::asio::io_service io_service;
    void on_read_header(const std::string&);
    std::map<std::string, std::string> headers;

    void ReadAuth();

private:
    tcp::acceptor acceptor;
    boost::shared_ptr<std::thread> sThread;

    void thread_main();
    void start_accept();
    void handle_accept(const boost::shared_ptr<Request>&, const boost::system::error_code&);

    std::string urlDecode(const std::string&);
};

#endif //BROKERAPP_HTTPSERVER_H
