//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeSubplotRenderer.h"
#include "VolumeData.h"
#include "VolumeRenderer.h"

#define dataHist (*_ticker->getBarHistory())

VolumeSubplotRenderer::VolumeSubplotRenderer(Ticker* ticker) : SubplotRenderer(ticker) {
    _title = "Volume";
    setFlags(ImPlotFlags_NoMenus);
    addVolumeItem();
}

void VolumeSubplotRenderer::addVolumeItem() {//Add Volume Item
    std::__1::shared_ptr<VolumeData> volume = std::__1::make_unique<VolumeData>(_ticker);
    volume->setPriority(1);
    std::__1::shared_ptr<VolumeRenderer> volumeR = std::__1::make_unique<VolumeRenderer>(_ticker->getContext(), volume.get());
    items.push_back(volumeR);
}


void VolumeSubplotRenderer::onPreRender() {}

void VolumeSubplotRenderer::onSetupPlot() {

//    ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time|ImPlotAxisFlags_NoTickLabels,
//                      ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
//    ImPlot::SetupAxisLimits(ImAxis_X1, dataHist.getData(BarDataType::TIME)[_lastIdxToPlot],
//                            dataHist.getData(BarDataType::TIME)[_lastIdxX],BarDataType::TIME);
//    ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");
//    ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = _ticker->getZoomOutMax();
//
//    if(_forceChangeMax) {
//        int posIdxMax = int((dataHist.size() - 1)*_positionerValue);
//        int posIdxMin = posIdxMax - _ticker->getMaxBarsToRender() < 0 ? 0 : posIdxMax - _ticker->getMaxBarsToRender();
//
//        _movedMin = dataHist.getData(BarDataType::TIME)[posIdxMin];
//        _movedMax = dataHist.getData(BarDataType::TIME)[posIdxMax];
//
//        ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetMin(_movedMin);
//        ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetMax(_movedMax);
//    }
}

void VolumeSubplotRenderer::onPostRender() {}

