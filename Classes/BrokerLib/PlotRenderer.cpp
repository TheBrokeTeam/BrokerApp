//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "PlotRenderer.h"
#include "../Helpers/Utils.h"
//#include "../Helpers/PlotHelper.h"
#include "../Widgets/IndicatorsView.h"
#include "../Contexts/Context.h"

PlotRenderer::PlotRenderer(Context *context) {
    _plotId = uuid::generate_uuid_v4();
    _plotName = "##" + _plotId;
    _context = context;
}

const std::string& PlotRenderer::getName() {
    return _name;
}

const std::string& PlotRenderer::getPlotName() {
    return _plotName;
}

const std::string &PlotRenderer::getId() {
    return _plotId;
}

void PlotRenderer::render() {
    if(onPreRender())
    {
        if (_isSubplot)
            onSetupPlot();

        onRender();
        onPopupRender();
        onPostRender();
    }
}

void PlotRenderer::onRender(){}

void PlotRenderer::onSetupPlot(){}

void PlotRenderer::setPlotName(const std::string& name) {
    _plotName = name + "##" + _plotId;
    _name = name;
}

void PlotRenderer::onPopupRender() {}

PlotRenderer::~PlotRenderer() {
    _name = "";
}

int PlotRenderer::getRenderStartIndex(double time,const std::vector<double>& timeArr) {
    int startIdx = PlotHelper::BinarySearch(timeArr.data(), 0, timeArr.size(),time);

    if(startIdx == -1)
        startIdx = 0;

    return startIdx;
}

int PlotRenderer::getRenderEndIndex(double time,const std::vector<double>& timeArr) {
    int endIdx = PlotHelper::BinarySearch(timeArr.data(), 0, timeArr.size(),time);

    if(endIdx == -1)
        endIdx = timeArr.size() - 1;

    return endIdx;
}

IndicatorRendererInfo PlotRenderer::getRenderInfo(Ticker *ticker,const std::vector<double>& timeArr) {
    IndicatorRendererInfo info;
    info.startIndex = getRenderStartIndex(ticker->getRenderRange().startTime,timeArr);
    auto endIndex = getRenderEndIndex(ticker->getRenderRange().endTime,timeArr);
    info.size = endIndex - info.startIndex + 1;
    if( info.size < 0)
        info.size = 0;
    return  info;
}

bool PlotRenderer::getIsSubplot() {
    return _isSubplot;
}

void PlotRenderer::setIsSubplot(bool isSubplot) {
    _isSubplot = isSubplot;
}

