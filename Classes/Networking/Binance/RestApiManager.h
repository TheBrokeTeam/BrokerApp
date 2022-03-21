//
// Created by Arthur Abel Motelevicz on 20/02/22.
//

#ifndef BROKERAPP_RESTAPIMANAGER_H
#define BROKERAPP_RESTAPIMANAGER_H

#include <memory>
#include <binapi/api.hpp>
#include <binapi/websocket.hpp>
#include "../../Data/Symbol.h"

class RestApiManager {
public:
    typedef std::function<void(std::vector<TickData>& data)> CandlesCallback;

    RestApiManager();
    ~RestApiManager();

    void getCandles(const Symbol& symbol,const CandlesCallback& callback);

private:
    void getKlinesAsync();
    std::unique_ptr<boost::asio::io_context> _apictx{nullptr};
    std::unique_ptr<binapi::rest::api> _api{nullptr};
    binapi::ws::websockets::handle _handler{nullptr};
};


#endif //BROKERAPP_RESTAPIMANAGER_H
