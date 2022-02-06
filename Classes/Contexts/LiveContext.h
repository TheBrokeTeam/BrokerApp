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

class LiveContext : public Context {
public:
    LiveContext(Editor* editor);
    void initialize() override;

    Ticker* fetchDataSymbol(Symbol symbol) override;
    void loadTicker() override;
    void handleDragDrop(PlotItem *plotItem) override;
    void openSymbolStream(const Symbol& symbol) override;
    void closeSymbolStream(const Symbol& symbol) override;

    std::shared_ptr<Indicator> loadIndicator(IndicatorsView::CandleIndicatorsTypes type,bool shouldCreateNode) override;

    void removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) override;
    void removeAllIndicators() override;

    void plotIndicators() override;
    void plotSubplotIndicators() override;
    void showTabBars(bool show) override;
private:
    std::shared_ptr<Ticker> _ticker{nullptr};
    std::vector<TickData> _data;
    binance::SocketManager _socket_manager;
};

#endif //BROKERAPP_LIVECONTEXT_H
