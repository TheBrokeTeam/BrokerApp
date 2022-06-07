////
//// Created by Maykon Meneghel on 21/04/22.
////
//
//#ifndef BROKERAPP_REQUEST_H
//#define BROKERAPP_REQUEST_H
//
//#include <iostream>
//#include <ostream>
//#include <istream>
//#include <ctime>
//#include <string>
//#include <boost/asio.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/enable_shared_from_this.hpp>
//#include <boost/thread.hpp>
//#include <algorithm>
//#include "../../Common/Json/BAJson.h"
//#include "../../Contexts/Context.h"
//
//using boost::asio::ip::tcp;
//class HttpServer;
//
//class Request : public boost::enable_shared_from_this<Request>
//{
//    static std::string make_daytime_string();
//
//    // member variables
//    HttpServer& server;
//    boost::asio::streambuf request;
//
//    void afterRead( const boost::system::error_code& ec, std::size_t bytes_transferred);
//    void afterWrite( const boost::system::error_code& ec, std::size_t bytes_transferred) const;
//
//public:
//    boost::shared_ptr<tcp::socket> socket;
//    explicit Request(HttpServer& server);
//    void answer();
//
//};
//
//
//#endif //BROKERAPP_REQUEST_H
