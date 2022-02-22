//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "PlotRenderer.h"
#include "../Helpers/Utils.h"
#include "../Helpers/PlotHelper.h"
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
        popupRender();
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

void PlotRenderer::resetPlot() {
    _time.clear();
}

const std::vector<double> &PlotRenderer::getTime() {
    return _time;
}

const int PlotRenderer::getSize() {
    return _time.size();
}

PlotRenderer::~PlotRenderer() {
    _name = "";
    _time.clear();
}

int PlotRenderer::getRenderStartIndex(double time) {
    int startIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(),time);

    if(startIdx == -1)
        startIdx = 0;

    return startIdx;
}

int PlotRenderer::getRenderEndIndex(double time) {
    int endIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(),time);

    if(endIdx == -1)
        endIdx = _time.size() - 1;

    return endIdx;
}

IndicatorRendererInfo PlotRenderer::getRenderInfo(Ticker *ticker) {
    IndicatorRendererInfo info;
    info.startIndex = getRenderStartIndex(ticker->getRenderRange().startTime);
    auto endIndex = getRenderEndIndex(ticker->getRenderRange().endTime);
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

