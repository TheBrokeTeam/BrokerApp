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
#include <algorithm>
#include "../../Common/Json/BAJson.h"
#include "../../Contexts/Context.h"

using boost::asio::ip::tcp;

class Request;

class HttpServer
{
public:
    explicit HttpServer(Context*, unsigned int);
    ~HttpServer() { if (sThread) sThread->join(); }
    void Run();
    void Stop();
    boost::asio::io_service io_service;
    void on_read_header(const std::string&);
    std::map<std::string, std::string> headers;

    bool ReadAuth(boost::asio::streambuf&);

private:
    Context* context;
    tcp::acceptor acceptor;
    boost::shared_ptr<std::thread> sThread;

    void thread_main();
    void start_accept();
    void handle_accept(const boost::shared_ptr<Request>&, const boost::system::error_code&);

    std::string urlDecode(const std::string&);
};

#endif //BROKERAPP_HTTPSERVER_H