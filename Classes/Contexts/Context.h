//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_CONTEXT_H
#define BROKERAPP_CONTEXT_H

#include <vector>
#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Tickers/Ticker.h"
#include "../Widgets/Widget.h"
#include "../Editor.h"
#include "../Widgets/IndicatorsView.h"
#include "../Tickables/Strategies/Strategy.h"
#include "../Nodes/INode.h"
#include "../Helpers/graph.h"
#include "../Data/Order.h"
#include "../Common/DataBase/Paths.h"
#include "../Common/DataBase/DBManager.h"
#include "../Data/User.h"
#include "../Common/Json/BAJson.h"

class Context {

public:
    explicit Context(Editor* editor);
    virtual ~Context();
//    virtual void loadSymbol(Symbol symbol) = 0;
    virtual Ticker* fetchDataSymbol(Symbol) = 0;
    bool startFetching = false;
    bool startSpinner = false;
    virtual void loadTicker() = 0;
    virtual void updateData(float dt);
    virtual void startSimulation(Ticker* ticker){};
    virtual void setSimulationSpeed(float speed){};
    virtual bool isSimulating(){return false;};

    virtual void openUserDataStream() {};
    virtual void openOrder(const Symbol &symbol) {};
    virtual void closeAllOrders(const Symbol &symbol) {};
    virtual double getCurrentTimeStamp() = 0 ;

    virtual void initialize() = 0;
    virtual void updateUI(float dt);

    virtual std::shared_ptr<Indicator> loadIndicator(IndicatorsView::CandleIndicatorsTypes type, bool shouldCreateNode = false, std::optional<ImVec2> pos = std::nullopt) = 0;
    virtual std::shared_ptr<INode> createIndicatorNode(UiNodeType type, std::shared_ptr<Indicator> indicator, std::optional<ImVec2> pos = std::nullopt){
        return nullptr;
    };
    virtual std::shared_ptr<INode> createNode(std::shared_ptr<graph::Graph<GraphNode>> _graph, UiNodeType type, std::optional<ImVec2> pos = std::nullopt, bool shouldCreateIndicatorNode = false) {
        return nullptr;
    };

    virtual void removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) = 0;
    virtual void removeAllIndicators() = 0;

    virtual void plotIndicators() = 0;
    virtual void plotSubplotIndicators() = 0;
    virtual void plotStrategy(){};
    virtual void handleDragDrop(PlotItem *plotItem) = 0;

    int getSubplotIndicatorsCount(){
        return _subplotIndicators.size();
    }

    template<typename T>
    T* getWidget()
    {
        for (const auto& widget : _widgets)
        {
            if (T* widget_t = dynamic_cast<T*>(widget.get()))
            {
                return widget_t;
            }
        }

        return nullptr;
    }

    template<typename T>
    void showWidget(bool show) {
        auto widget =  getWidget<T>();
        if(widget)
            widget->SetVisible(show);
    }

    template<typename T>
    std::vector<T*> getIndicator()
    {
        std::vector<T*> out;
        for (const auto& indicator : _indicators)
        {
            if (T* widget_t = dynamic_cast<T*>(indicator.get()))
            {
                out.push_back(widget_t);
            }
        }

        return out;
    }

    Indicator* getIndicatorById(const std::string& id);
//    Strategy* getStrategyById(const std::string& id);

    Indicator* getIndicatorByName(const std::string& name);
//    Strategy* getStrategyByName(const std::string& id);


    const std::vector<std::shared_ptr<Widget>>& getWidgets();
    Editor* getEditor();
    DBManager* getDBManager();

    //developer phase
    virtual void showTabBars(bool show) = 0;

    bool getShouldRender() const;
    void setShouldRender(bool);
    virtual void openSymbolStream(const Symbol& symbol){};
    virtual void closeSymbolStream(const Symbol& symbol){};

    virtual void fetchUserAccountInfo(){};

    // login stuffs
    bool _sentAuthentication = false;
    bool _startingAuthentication = false;
    bool userSelected();
    User* getUser();
    void addUser(const rapidjson::Document &doc);
    void logout();

    virtual std::vector<Bot> getBots(){};
    virtual void addBot(const Bot&){};

    virtual void setStrategyEditor(StrategyEditor* strategyEditor){};
    virtual StrategyEditor* getStrategyEditor(){};


    void selectBot(const Bot&);
//    void deselectBot();
//    bool isSelectedBot();

protected:
    std::vector<std::shared_ptr<Widget>> _widgets;
    std::vector<std::shared_ptr<Indicator>> _indicators;
    std::vector<std::shared_ptr<Indicator>> _subplotIndicators;

    std::vector<Order> _orders;

    std::optional<Bot> _currentBot = std::nullopt;

    virtual void loadBot(){};
    //    std::vector<std::shared_ptr<Strategy>> _bots;
    std::vector<std::shared_ptr<INode>> _nodes;

    Editor* _editor{nullptr};
    User* _user{nullptr};
    DBManager _dbManager;


    void loadUser();

    bool _shouldRender = false;
};

#endif //BROKERAPP_CONTEXT_H
