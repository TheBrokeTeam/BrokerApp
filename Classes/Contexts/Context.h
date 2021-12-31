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

class Context {
public:
    Context(Editor* editor);

    virtual Ticker* loadSymbol(const Symbol& symbol) = 0;
    virtual void loadTicker() = 0;
    virtual void updateData(float dt);
    virtual void startSimulation(Ticker* ticker) = 0;
    virtual void setSimulationSpeed(float speed) = 0;
    virtual bool isSimulating()  = 0;

    virtual void initialize() = 0;
    virtual void updateUI(float dt);

    virtual void loadIndicator(IndicatorsView::CandleIndicatorsTypes type) = 0;
    virtual void plotIndicators() = 0;
    virtual void plotStrategy() = 0;


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
    Strategy* getStrategyById(const std::string& id);

    Indicator* getIndicatorByName(const std::string& name);
    Strategy* getStrategyByName(const std::string& id);


    const std::vector<std::shared_ptr<Widget>>& getWidgets();
    Editor* getEditor();

    //developer phase
    virtual void showTabBars(bool show) = 0;
protected:
    std::vector<std::shared_ptr<Widget>> _widgets;
    std::vector<std::shared_ptr<Indicator>> _indicators;
    std::vector<std::shared_ptr<Strategy>> _strategies;


    Editor *_editor{nullptr};
};

#endif //BROKERAPP_CONTEXT_H
