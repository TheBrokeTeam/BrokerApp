//
// Created by Luiz Veloso on 02/03/22.
//

#include "MainSubplotRenderer.h"
#include "OHLCData.h"
#include "OHLCRenderer.h"
#include "../../Helpers/PlotHelper.h"
#include "DataSeriesRenderer.h"

#define dataHist (*_ticker->getBarHistory())

MainSubplotRenderer::MainSubplotRenderer(Ticker* ticker) : SubplotRenderer(ticker) {
    _title = "OHLC";
    setFlags(ImPlotFlags_NoMenus);
}

void MainSubplotRenderer::addOHLCItem(OHLCData* ohlcData) {//Add OHLC Item
//    std::__1::shared_ptr<OHLCData> ohlc = std::__1::make_unique<OHLCData>(_ticker);
//    ohlc->setPriority(1);
    std::__1::shared_ptr<OHLCRenderer> ohlcR = std::__1::make_unique<OHLCRenderer>(_ticker->getContext(), ohlcData);
    items.push_back(ohlcR);
}

void MainSubplotRenderer::onPreRender() {

}

void MainSubplotRenderer::onSetupPlot() {
//    ImPlotRect bnds = ImPlot::GetPlotLimits();
//    double minX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Min), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
//    double maxX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Max), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
//    double startTime = minX;
//    double endTime = maxX;
//
//    if (startTime <  dataHist.getData(BarDataType::TIME).front()) startTime = dataHist.getData(BarDataType::TIME).front();
//    if (endTime >  dataHist.getData(BarDataType::TIME).back()) endTime = dataHist.getData(BarDataType::TIME).back();
//
//    if (startTime >  dataHist.getData(BarDataType::TIME).back()) startTime = dataHist.getData(BarDataType::TIME).front();
//    if (endTime <  dataHist.getData(BarDataType::TIME).front()) endTime = dataHist.getData(BarDataType::TIME).back();
//
//    _ticker->updateRenderRange(startTime,endTime);
//    auto renderInfo = DataSeriesRenderer::getRenderInfo(_ticker,_ticker->getBarHistory()->getData(BarDataType::TIME));


    ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time,
                      ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
    ImPlot::SetupAxisLimits(ImAxis_X1, dataHist.getData(BarDataType::TIME_S)[_renderInterval.startIndex],
                            dataHist.getData(BarDataType::TIME_S)[_renderInterval.endIndex]);
    ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");
    ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = _ticker->getZoomOutMax();
//    ImPlot::SetupAxisLimits(ImAxis_X1, dataHist.getData(BarDataType::TIME)[renderInfo.startIndex],
//                            dataHist.getData(BarDataType::TIME)[renderInfo.startIndex+renderInfo.size]);
}

void MainSubplotRenderer::onPostRender() {}

