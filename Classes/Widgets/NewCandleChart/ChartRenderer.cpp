//
// Created by Luiz Veloso on 02/03/22.
//

#include "ChartRenderer.h"
#include "BrokerColorsImgui.h"

#define dataHist (*_ticker->getBarHistory())

ChartRenderer::ChartRenderer(Ticker *ticker): _ticker(ticker) {}

std::vector<float> ChartRenderer::calculateRatios() {

    std::vector<float> ratios;

    ratios.push_back(5);

    for (int i = 0; i < subplots.size(); i++) {
        ratios.push_back(2);
    }

    ratios.push_back(3);

    while (ratios.size() < subplots.size() + _maxSubplots) {
        ratios.push_back(0);
    }

    return ratios;
}



int ChartRenderer::getLastIdxX() const {
    return _ticker->getBarHistory()->size() - 1;
}

int ChartRenderer::getLastIdxToPlot() const {
    int numberOfBarsToRender = _ticker->getBarHistory()->size() > _ticker->getMaxBarsToRender() ? _ticker->getMaxBarsToRender() : _ticker->getBarHistory()->size();
    return _lastIdxX - numberOfBarsToRender  < 0  ? 0 :  _lastIdxX - numberOfBarsToRender ;
}


void ChartRenderer::addPlotToChart(std::shared_ptr<SubplotRenderer> subplot) {
    subplots.push_back(subplot);
}

void ChartRenderer::removePlotFromChart(std::shared_ptr<SubplotRenderer> subplot) {
    subplots.erase(std::remove(subplots.begin(), subplots.end(), subplot), subplots.end());
}


ImPlotSubplotFlags ChartRenderer::getFlags() const {
    return _flags;
}

void ChartRenderer::setFlags(ImPlotSubplotFlags flags) {
    _flags = flags;
}

//MARK: lifecycle

void ChartRenderer::render() {
    onPreRender();
    if (onBeginRender()) {
        onRender();
        onEndRender();
    }
    onPostRender();
}


void ChartRenderer::onPreRender() {
    ImPlot::FormatDate(_t1,_t1_str,32,ImPlotDateFmt_DayMoYr,true);
    ImPlot::FormatDate(_t2,_t2_str,32,ImPlotDateFmt_DayMoYr,true);
    _t1 = ImPlot::AddTime(_t2, ImPlotTimeUnit_Yr, -1);
//
//    setupSlider();
}


bool ChartRenderer::onBeginRender() {
    return  ImPlot::BeginSubplots(getName() , _maxSubplots, 1, ImVec2(-1, -1), _flags, calculateRatios().data());
}

void ChartRenderer::onRender() {
    for (auto& i: subplots) {
        i->render();
    }
}

void ChartRenderer::onEndRender() {
    ImPlot::EndSubplots();

}

void ChartRenderer::onPostRender() {}

const char *ChartRenderer::getName() const {
    return _name.c_str();
}

void ChartRenderer::setName(const std::string &name) {
    _name = ((_showTitle ? "" : "##") + name);
}

void ChartRenderer::setDelegate(ChartRendererDelegate *delegate) {
    ChartRenderer::_delegate = delegate;
}

void ChartRenderer::updateRenderInterval(int startIndex, int endIndex) {
    _renderInterval.startIndex = startIndex;
    _renderInterval.endIndex = endIndex;

    for (auto& i: subplots) {
        i->updateRenderInterval( startIndex,  endIndex) ;
    }
}

void ChartRenderer::subplotDidScroll(int startIndex, int endIndex, SubplotRenderer *sender) {

    for (auto& i : subplots) {

        //LV: Can't update the sender subplot
        if (sender != i.get()) //LV: should be !==? How do I compare address?
            i->updateRenderInterval(startIndex, endIndex);

    }
}


