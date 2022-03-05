//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeRenderer.h"
#include "implot.h"

VolumeRenderer::VolumeRenderer(Context *context, VolumeData *data): DataSeriesRendererImgui(context) {
    _data = data;
    setPlotName("Volume");
}

void VolumeRenderer::onRender() {
    //todo: Faz diferença se é o _data->getTime() ou o time associado ao ticker->BarHistory?
    auto renderInfo = getRenderInfo(_data->getTicker(), _data->getTime());
    const double candleWidth = _data->getTicker()->getSymbol()->getTimeIntervalInMinutes() * 60;

    ImPlot::PlotBars("Volume",&_data->getTime()[renderInfo.startIndex],&_data->getData()[renderInfo.startIndex],renderInfo.size, candleWidth*0.5);
}

void VolumeRenderer::onPopupRender() {}

VolumeRenderer::~VolumeRenderer() {}

