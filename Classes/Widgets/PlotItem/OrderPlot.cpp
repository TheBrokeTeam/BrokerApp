//
// Created by Arthur Abel Motelevicz on 26/03/22.
//

#include "OrderPlot.h"


OrderPlot::OrderPlot(Context *c, std::shared_ptr<Order> order): PlotItem(c) {
    _order = std::move(order);
}

void OrderPlot::resetPlot() {
    PlotItem::resetPlot();
}

void OrderPlot::onRender() {
    ImDrawList* drawList =  ImPlot::GetPlotDrawList();
    ImPlot::SetNextLineStyle(_color,_lineWidth);

    //horizontal dashed line
    double tool_l_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos()).x;
    double tool_r_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos() + ImPlot::GetPlotSize()).x;

    double sizeX = tool_r_h - tool_l_h;
    int steps = 101;
    double step = sizeX/steps;

    for(int i = 0; i < steps; i+=2) {
        ImVec2 leftPos = ImPlot::PlotToPixels(tool_l_h + i*step, _order->price);
        ImVec2 rightPos = ImPlot::PlotToPixels(tool_l_h + (i+1) * step, _order->price);
        drawList->AddLine(leftPos, rightPos, IM_COL32(128, 128, 128, 64), 2.0f);
    }

    ImPlot::TagY(_order->price, _color);
}

