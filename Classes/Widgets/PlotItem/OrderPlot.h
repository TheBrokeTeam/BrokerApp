//
// Created by Arthur Abel Motelevicz on 26/03/22.
//

#ifndef BROKERAPP_ORDERPLOT_H
#define BROKERAPP_ORDERPLOT_H


#include "../../Widgets/PlotItem/PlotItem.h"
#include "../../Data/Order.h"

class OrderPlot: public PlotItem {
public:
    OrderPlot(Context* c, std::shared_ptr<Order> order);
    void resetPlot() override;
    void onRender() override;

private:
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;

    std::shared_ptr<Order> _order{nullptr};
};


#endif //BROKERAPP_ORDERPLOT_H
