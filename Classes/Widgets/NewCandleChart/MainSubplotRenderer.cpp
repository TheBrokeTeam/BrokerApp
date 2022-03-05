//
// Created by Luiz Veloso on 02/03/22.
//

#include "MainSubplotRenderer.h"
#include "OHLCData.h"
#include "OHLCRenderer.h"

#define dataHist (*_ticker->getBarHistory())

MainSubplotRenderer::MainSubplotRenderer(Ticker* ticker) : SubplotRenderer(ticker) {
    _title = "OHLC";
    setFlags(ImPlotFlags_NoMenus);
    addOHLCItem();
}

void MainSubplotRenderer::addOHLCItem() {//Add OHLC Item
    std::__1::shared_ptr<OHLCData> ohlc = std::__1::make_unique<OHLCData>(_ticker);
    ohlc->setPriority(1);
    std::__1::shared_ptr<OHLCRenderer> ohlcR = std::__1::make_unique<OHLCRenderer>(_ticker->getContext(), ohlc.get());
    items.push_back(ohlcR);
}

void MainSubplotRenderer::onPreRender() {}

void MainSubplotRenderer::onSetupPlot() {

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

void MainSubplotRenderer::onPostRender() {}

