//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_LIVECONTEXT_H
#define BROKERAPP_LIVECONTEXT_H

#include "Context.h"
#include "../Nodes/UiNodeType.h"
#include <map>
#include <set>
#include <rapidjson/document.h>
#include "../Networking/Binance/SocketManager.h"
#include "../Networking/Binance/RestApiManager.h"

class LiveContext : public Context {
public:

    LiveContext(Editor* editor);
    ~LiveContext();
    void initialize() override;
    void updateData(float dt) override;
    double getCurrentTimeStamp() override;


    Ticker* fetchDataSymbol(Symbol symbol) override;
    void fetchUserAccountInfo() override;

    void loadTicker() override;
    void handleDragDrop(PlotItem *plotItem) override;
    void openSymbolStream(const Symbol& symbol) override;
    void closeSymbolStream(const Symbol& symbol) override;

    void openUserDataStream() override;

    void openOrder(const Order &order) override;
    void closeAllOrders(const Symbol &symbol) override;

    std::shared_ptr<Indicator> loadIndicator(IndicatorsView::CandleIndicatorsTypes type,bool shouldCreateNode) override;

    void removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) override;
    void removeAllIndicators() override;

    void plotIndicators() override;
    void plotSubplotIndicators() override;
    void plotOrders() override;
    void showTabBars(bool show) override;
private:
    void openSymbolCandleSocket(const Symbol& symbol);
    void openSymbolTradeSocket(const Symbol& symbol);

    std::vector<SocketManager::StreamCallback> _streams;
    std::shared_ptr<Ticker> _ticker{nullptr};

    //On live context - data should be used just to load some history data
    //and call loadticker
    std::vector<TickData> _data;

    double _currentTimeStamp = 0;
    void removeOrderById(const std::string& id);
    void updateOrders(const Order& order);
    std::mutex _orderMutex;
};

#endif //BROKERAPP_LIVECONTEXT_H
