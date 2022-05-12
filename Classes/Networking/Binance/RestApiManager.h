//
// Created by Arthur Abel Motelevicz on 20/02/22.
//

#ifndef BROKERAPP_RESTAPIMANAGER_H
#define BROKERAPP_RESTAPIMANAGER_H

#include <memory>
#include <binapi/api.hpp>
#include <binapi/websocket.hpp>
#include "../../Data/Symbol.h"
#include "SymbolInfo.h"
#include "../../Data/Order.h"
#include "../../Data/AccountInfo.h"


class RestApiManager {
public:
    typedef std::function<void(std::vector<TickData>& data)> CandlesCallback;
    typedef std::function<void(Order& order)> OrderCallback;
    typedef std::function<void(bool success, const std::string listenKey)> UserDataStreamCallback;
    typedef std::function<void(AccountInfo& info)> AccountInfoCallback;


    typedef std::function<void(bool success, const std::vector<SymbolInfo>)> ExchangeInfoCallback;

    RestApiManager();
    ~RestApiManager();

    void getExchangeInfo(ExchangeInfoCallback callback);
    void getCandles(const Symbol& symbol,const CandlesCallback& callback);
    void openOrder(const Symbol& symbol,const OrderCallback& callback);
    void accountInfo(const AccountInfoCallback& callback);
    void startUserDataStream(UserDataStreamCallback callback);
    void cancelOrder(Order& order);
    void initialize(const std::string& pk, const std::string& sk);

private:
    void runApiAsync();

    std::unique_ptr<boost::asio::io_context> _apictx{nullptr};
    std::unique_ptr<binapi::rest::api> _api{nullptr};

};


#endif //BROKERAPP_RESTAPIMANAGER_H
