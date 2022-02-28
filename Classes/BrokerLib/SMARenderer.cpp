//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "SMARenderer.h"
#include "../Tickers/Ticker.h"
#include "../Contexts/Context.h"

SMARenderer::SMARenderer(Context *context, SMAData* data): PlotRendererImgui(context) {
    _data = data;
    setPlotName("SMA");
};

SMARenderer::~SMARenderer() = default;

void SMARenderer::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_data->getTicker(),_data->getTime());
    ImPlot::PlotLine(_plotName.c_str(), &_data->getTime()[renderInfo.startIndex], &_data->getData()[renderInfo.startIndex], renderInfo.size);
}
void SMARenderer::onPopupRender()
{
        //call the popup to custom controllers on subclasses
         int as = _data->getAverageSize();
         if(ImGui::SliderInt("Average size", &as, 1, 200)){
             _data->resetData();
             _data->setAverageSize(as);
             _data->onLoad(_data->getTicker()->getBarHistory());
         }
         ImGui::ColorEdit4("Color",&_color.x);
         ImGui::Separator();
         ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

