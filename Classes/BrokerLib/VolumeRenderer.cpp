//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeRenderer.h"
#include "implot.h"
#include "BrokerColorsImgui.h"

VolumeRenderer::VolumeRenderer(Context *context, VolumeData *data): DataSeriesRendererImgui(context) {
    _data = data;
    setPlotName("Volume");
}

void VolumeRenderer::onRender() {
    //LV: Faz diferença se é o _data->getTime() ou o time associado ao ticker->BarHistory?
//    Ticker* ticker = _data->getTicker();
//    int lastIdxX = ticker->getBarHistory()->size();
//    int numberOfBarsToRender = ticker->getBarHistory()->size() > ticker->getMaxBarsToRender() ? ticker->getMaxBarsToRender() : ticker->getBarHistory()->size();
//    int startIndex = lastIdxX - numberOfBarsToRender  < 0  ? 0 :  lastIdxX - numberOfBarsToRender ;

//    auto renderInfo = getRenderInfo(_data->getTicker(), _data->getTime());
    //const double candleWidth = _data->getTicker()->getSymbol()->getTimeIntervalInMinutes() * 60;

    ImPlot::SetNextFillStyle(BrokerColorsImgui::volume_color);
    //ImPlot::PlotBars("Volume",&_data->getTime()[renderInfo.startIndex],&_data->getData()[renderInfo.startIndex],renderInfo.size, candleWidth*0.5);
    ImPlot::PlotBars("Volume",&_data->getTime()[_renderInterval.startIndex],&_data->getData()[_renderInterval.startIndex], _renderInterval.size(), 2);

}

void VolumeRenderer::onPopupRender() {}

VolumeRenderer::~VolumeRenderer() {}

