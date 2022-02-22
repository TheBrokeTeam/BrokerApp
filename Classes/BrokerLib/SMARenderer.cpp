//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "SMARenderer.h"
#include "../Tickers/Ticker.h"

SMARenderer::SMARenderer(Context* context,SMAData* data):PlotRenderer(context){
    _data = data;
};

bool SMARenderer::onPreRender() {
    return ImPlot::BeginItem(_plotName.c_str());
}

void SMARenderer::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_data->getTicker());
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &_data->getData()[renderInfo.startIndex], renderInfo.size);
}
void SMARenderer::onPopupRender() {
    int as = _data->getAverageSize();
    if(ImGui::SliderInt("Average size", &as, 1, 200)){
        resetPlot();
        _data->setAverageSize(as);
        _data->onLoad(_data->getTicker()->getBarHistory());
    }
    ImGui::ColorEdit4("Color",&_color.x);
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void SMARenderer::onPostRender() {
    ImPlot::EndItem();
}

void SMARenderer::resetPlot() {
    PlotRenderer::resetPlot();
}

const ImVec4 &SMARenderer::getColor() {
    return _color;
}

void SMARenderer::setColor(ImVec4 &color) {
    _color = color;
}
