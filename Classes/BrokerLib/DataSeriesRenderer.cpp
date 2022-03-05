//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "DataSeriesRenderer.h"
#include "../Helpers/Utils.h"
//#include "../Helpers/PlotHelper.h"
#include "../Widgets/IndicatorsView.h"
#include "../Contexts/Context.h"

DataSeriesRenderer::DataSeriesRenderer(Context *context) {
    _plotId = uuid::generate_uuid_v4();
    _plotName = "##" + _plotId;
    _context = context;
}

const std::string& DataSeriesRenderer::getName() {
    return _name;
}

const std::string& DataSeriesRenderer::getPlotName() {
    return _plotName;
}

const std::string &DataSeriesRenderer::getId() {
    return _plotId;
}

void DataSeriesRenderer::render() {
    if(onPreRender())
    {
        if (_isSubplot)
            onSetupPlot();

        onRender();
        popupRender();

        if(_dragDropCallback)
            _dragDropCallback(this);

        onPostRender();
    }
}

void DataSeriesRenderer::onRender(){}

void DataSeriesRenderer::onSetupPlot(){}

void DataSeriesRenderer::setPlotName(const std::string& name) {
    _plotName = name + "##" + _plotId;
    _name = name;
}

void DataSeriesRenderer::onPopupRender() {}

DataSeriesRenderer::~DataSeriesRenderer() {
    _name = "";
}

int DataSeriesRenderer::getRenderStartIndex(double time, const std::vector<double>& timeArr) {
    int startIdx = PlotHelper::BinarySearch(timeArr.data(), 0, timeArr.size(),time);

    if(startIdx == -1)
        startIdx = 0;

    return startIdx;
}

int DataSeriesRenderer::getRenderEndIndex(double time, const std::vector<double>& timeArr) {
    int endIdx = PlotHelper::BinarySearch(timeArr.data(), 0, timeArr.size(),time);

    if(endIdx == -1)
        endIdx = timeArr.size() - 1;

    return endIdx;
}

IndicatorRendererInfo DataSeriesRenderer::getRenderInfo(Ticker *ticker, const std::vector<double>& timeArr) {
    IndicatorRendererInfo info;
    info.startIndex = getRenderStartIndex(ticker->getRenderRange().startTime,timeArr);
    auto endIndex = getRenderEndIndex(ticker->getRenderRange().endTime,timeArr);
    info.size = endIndex - info.startIndex + 1;
    if( info.size < 0)
        info.size = 0;
    return  info;
}

bool DataSeriesRenderer::getIsSubplot() {
    return _isSubplot;
}

void DataSeriesRenderer::setIsSubplot(bool isSubplot) {
    _isSubplot = isSubplot;
}

void DataSeriesRenderer::setDragDropCallback(const DataSeriesRenderer::DragDropCallback &dragDropCallback) {
    _dragDropCallback = dragDropCallback;
}



