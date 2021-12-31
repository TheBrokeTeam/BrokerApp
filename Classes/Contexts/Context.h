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
#include "../Widgets/Indicators.h"



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

    virtual void loadIndicator(Indicators::CandleIndicatorsTypes type) = 0;
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


    const std::vector<std::shared_ptr<Widget>>& getWidgets();
    Editor* getEditor();

protected:
    std::vector<std::shared_ptr<Widget>> _widgets;
    Editor *_editor{nullptr};
};

#endif //BROKERAPP_CONTEXT_H
