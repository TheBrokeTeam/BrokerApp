//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "LiveContext.h"
#include "../Tickables/Indicators/SMA.h"
#include "../Tickables/Indicators/Bollinger.h"
#include "../Tickables/Indicators/EMA.h"
#include "../Tickables/Indicators/TRIX.h"
#include "../Tickables/Indicators/WMA.h"
#include "../Tickables/Indicators/PSAR.h"
#include "../Tickables/Indicators/MFI.h"
#include "../Tickables/Indicators/VWAP.h"
#include "../Widgets/MainMenuBar.h"
#include "../Widgets/SocketStreamController.h"
#include "../Widgets/ChartView.h"
#include "../Widgets/StrategyEditor.h"
#include "../Helpers/Utils.h"
#include "../Widgets/PlotItem/OrderPlot.h"

static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                        "2h", "4h", "6h", "8h", "12h", "1d",
                                        "3d", "1w", "1mo"};

LiveContext::LiveContext(Editor *editor) : Context(editor) {
    _ticker.reset();
    _ticker = std::make_shared<Ticker>(this);
}

void LiveContext::initialize() {
    // Initialize the context
    _widgets.emplace_back(std::make_shared<MainMenuBar>(this));
    _widgets.emplace_back(std::make_shared<ChartView>(this));
    _widgets.emplace_back(std::make_shared<IndicatorsView>(this));
    _widgets.emplace_back(std::make_shared<SocketStreamController>(this));

    getWidget<IndicatorsView>()->setTrashCallback([this](){
        removeAllIndicators();
    });
}

void LiveContext::updateData(float dt) {
    Context::updateData(dt);
}

double LiveContext::getCurrentTimeStamp() {
    return TimeUtils::timeSinceEpochMillisec();
}

void LiveContext::loadTicker() {
    for(auto& d : _data)
        _ticker->tick(d);
}

std::shared_ptr<Indicator> LiveContext::loadIndicator(IndicatorsView::CandleIndicatorsTypes type, bool shouldCreateNode) {

    if(_ticker == nullptr)
        return nullptr;

    std::shared_ptr<Indicator> indicator{nullptr};

    switch (type) {
        case IndicatorsView::CandleIndicatorsTypes::SMA: {
            std::shared_ptr<SMA> sma = std::make_unique<SMA>(_ticker.get());
            sma->setPriority(1);
            _indicators.push_back(std::move(sma));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::SMA,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::BOLL: {
            std::shared_ptr<Bollinger> boll = std::make_shared<Bollinger>(_ticker.get());
            boll->setPriority(1);
            _indicators.push_back(std::move(boll));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::BOLL,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::EMA: {
            std::shared_ptr<EMA> ema = std::make_shared<EMA>(_ticker.get());
            ema->setPriority(1);
            _indicators.push_back(std::move(ema));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::EMA,_indicators.back());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::WMA: {

            std::shared_ptr<WMA> wma = std::make_shared<WMA>(_ticker.get());
            wma->setPriority(1);
            _indicators.push_back(std::move(wma));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::WMA,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::VWAP: {
            std::shared_ptr<VWAP> vwap = std::make_shared<VWAP>(_ticker.get());
            vwap->setPriority(1);
            _indicators.push_back(std::move(vwap));
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::VWAP,_indicators.back());

        }
            break;

        case IndicatorsView::CandleIndicatorsTypes::TRIX:
        {
            std::shared_ptr<TRIX> trix = std::make_shared<TRIX>(_ticker.get());
            trix->setPriority(1);
            _subplotIndicators.push_back(std::move(trix));
            indicator = _subplotIndicators.back();
            _ticker->addTickable(_subplotIndicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::TRIX,_subplotIndicators.back());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::PSAR :
        {
            std::shared_ptr<PSAR> psar = std::make_shared<PSAR>(_ticker.get());
            psar->setPriority(1);
            _indicators.push_back(std::move(psar));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::PSAR,_indicators.back());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::MFI :
        {
            std::shared_ptr<MFI> mfi = std::make_shared<MFI>(_ticker.get());
            mfi->setPriority(1);
            _subplotIndicators.push_back(std::move(mfi));
            indicator = _subplotIndicators.back();
            _ticker->addTickable(_subplotIndicators.back().get());
        }
            break;
        default:
            break;
    }

    return indicator;
}

void LiveContext::plotIndicators() {
    for(auto& i : _indicators) {
        i->render();
    }
}

//develop phase
void LiveContext::showTabBars(bool show) {
    for(auto& w : getWidgets()){
        w->showTabBar(show);
    }
    Editor::show_tabbars = show;
}


void LiveContext::removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) {

    //first delete from ticker
    if(_ticker->removeTickable(indicator.get()))
        puts("indicator removed successfully");

    //now delete from indicators list
    for(auto it = _indicators.begin(); it != _indicators.end(); it++){
        if((*it)->getId() == indicator->getId())
        {
            if (shouldDeleteNode)
                getWidget<StrategyEditor>()->removeNodeIndicator(indicator);

            _indicators.erase(it);
            break;
        }
    }

    //now delete from indicators list
    for(auto it = _subplotIndicators.begin(); it != _subplotIndicators.end(); it++){
        if((*it)->getId() == indicator->getId())
        {
            if (shouldDeleteNode)
                getWidget<StrategyEditor>()->removeNodeIndicator(indicator);

            _subplotIndicators.erase(it);
            break;
        }
    }
}

void LiveContext::removeAllIndicators() {
    auto strategyEditor = getWidget<StrategyEditor>();
    for(auto& i : _indicators){
        strategyEditor->removeNodeIndicator(i);
        if(_ticker->removeTickable(i.get()))
            puts("indicator removed successfully");
    }

    for(auto& i : _subplotIndicators){
        strategyEditor->removeNodeIndicator(i);
        if(_ticker->removeTickable(i.get()))
            puts("indicator removed successfully");
    }

    _indicators.clear();
    _subplotIndicators.clear();
}

void LiveContext::plotSubplotIndicators() {
    for(auto& i : _subplotIndicators) {
        i->render();
    }
}

void LiveContext::handleDragDrop(PlotItem *plotItem) {
    std::shared_ptr<Indicator> ind{nullptr};

    for(auto& i : _subplotIndicators) {
        if (i.get() == plotItem) {
            ind = i;
        }
    }

    for(auto& i : _indicators) {
        if (i.get() == plotItem) {
            ind = i;
        }
    }

    if (ind != nullptr) {
        if (ImPlot::BeginDragDropSourceItem(ind->getPlotName().c_str())) {
            ImGui::SetDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID_REMOVING, &ind,
                                      sizeof(std::shared_ptr<Indicator>));
            ImPlot::EndDragDropSource();
        }
    }
}

Ticker *LiveContext::fetchDataSymbol(Symbol symbol) {
    _ticker->reset();
    _ticker->setSymbol(symbol);

    _data.clear();

    _data = symbol.fetchCSVData();

    loadTicker();

    setShouldRender(true);
    auto chart = getWidget<ChartView>();

    chart->addChart(std::make_shared<CandleChart>(this,_ticker.get()));

    return _ticker.get();
}

void LiveContext::openSymbolStream(const Symbol& symbol) {

    _ticker->reset();
    _ticker->setSymbol(symbol);

//    TODO:: load some history data
//   _data.clear();
    RestApiManager::CandlesCallback candlesCallback = [this,symbol](std::vector<TickData>& data){
       std::cout << data.size() << std::endl;
//       _data.swap(data);
        for(auto &d : data)
            _ticker->tick(d);

        openSymbolTradeSocket(symbol);
//        openSymbolCandleSocket(symbol);
    };

    getEditor()->getApiManager()->getCandles(symbol,candlesCallback);

//  add chart to render
    auto chart = getWidget<ChartView>();
    chart->addLiveChart(std::make_shared<LiveCandleChart>(this,_ticker.get()));
    setShouldRender(true);
}

void LiveContext::closeSymbolStream(const Symbol& symbol) {
    getEditor()->getSocketManager()->closeStream(symbol);
}

void LiveContext::openSymbolCandleSocket(const Symbol &symbol) {
//  open candle socket -----------------------------------
//Todo:: handle errors
    SocketManager::CandlesCallback candleCallback  = [this](std::vector<TickData>& data){
        for(auto &d : data)
            _ticker->tick(d);
    };

    getEditor()->getSocketManager()->openCandleStream(symbol,candleCallback);
//    ---------------------------------------------

}

void LiveContext::openSymbolTradeSocket(const Symbol &symbol) {

//  open socket -----------------------------------
//Todo:: handle errors
    SocketManager::StreamCallback streamCallback  = [this](const TickData& data){
        _ticker->tick(data,true);
    };

    _streams.push_back(streamCallback);

    getEditor()->getSocketManager()->openStream(symbol,streamCallback);
//    ---------------------------------------------
}

LiveContext::~LiveContext() {
    getEditor()->getSocketManager()->closeStream(*_ticker->getSymbol());
    getEditor()->getSocketManager()->closeCandleStream(*_ticker->getSymbol());
    getEditor()->getSocketManager()->closeUserDataStreamSocket();
}

void LiveContext::openUserDataStream() {
    getEditor()->getApiManager()->startUserDataStream([this](bool success,auto key){
       if(success) {
           fetchUserAccountInfo();
           getEditor()->getSocketManager()->openUserDataStream(key);
       }
    });
}

void LiveContext::openOrder(const Symbol &symbol) {
    getEditor()->getApiManager()->openOrder(symbol,[this](std::shared_ptr<Order> order){
        std::cout << "Order opened:" << order->clientOrderId << std::endl;
        _orders.push_back(std::move(order));
    });
}

void LiveContext::closeAllOrders(const Symbol &symbol) {
    for(auto& o :_orders){
        getEditor()->getApiManager()->cancelOrder(o,[this](std::shared_ptr<Order> order){
            std::cout << "Order opened:" << order->clientOrderId << std::endl;
            removeOrderById(order->clientOrderId);
        });
    }
}

void LiveContext::fetchUserAccountInfo() {
    getEditor()->getApiManager()->accountInfo([this](const AccountInfo& info){
        getDBManager()->updateUserData(info);
    });
}

void LiveContext::plotOrders() {
    for (auto &o :_orders) {
        auto op = OrderPlot(this, o);
        op.render();
    }
}
void LiveContext::removeOrderById(const std::string& id) {
    for(auto it = _orders.begin(); it != _orders.end(); it++){
        auto o = *it;
        if(o->clientOrderId == id){
            _orders.erase(it);
            return;
        }
    }
}
