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
    typedef std::function<void(bool success, const std::string listenKey)> UserDataStreamCallback;


    RestApiManager();
    ~RestApiManager();

    void getCandles(const Symbol& symbol,const CandlesCallback& callback);
    void openOrder(const Symbol& symbol,const CandlesCallback& callback);
    void accountInfo();
    void startUserDataStream(UserDataStreamCallback callback);


private:
    void getKlinesAsync();
    void openOrderAsync();

    std::unique_ptr<boost::asio::io_context> _apictx{nullptr};
    std::unique_ptr<binapi::rest::api> _api{nullptr};

};


#endif //BROKERAPP_RESTAPIMANAGER_H
