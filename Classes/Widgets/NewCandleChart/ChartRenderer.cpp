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


void ChartRenderer::setupSlider() {//SliderStuff
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 16);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, BrokerColorsImgui::broker_yellow_active);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, BrokerColorsImgui::broker_yellow);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, BrokerColorsImgui::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, BrokerColorsImgui::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, BrokerColorsImgui::broker_light_grey);

    if(ImGui::SliderFloat("##Positioner", &_positionerValue, 0.000f, 1.000f, "%.3f")){

        int posIdxMax = int((dataHist.size() - 1) * _positionerValue);
        int posIdxMin = posIdxMax - _ticker->getMaxBarsToRender() < 0 ? 0 : posIdxMax - _ticker->getMaxBarsToRender();

        movedMin = dataHist.getData(TIME)[posIdxMin];
        movedMax = dataHist.getData(TIME)[posIdxMax];
        forceChangeMax =  true;
    }
    else{
        //update postioner
        float posPercent = float(_lastIdxX + 1) / dataHist.size();
        _positionerValue = posPercent;
    }

    ImGui::PopStyleColor(5);
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


const char* ChartRenderer::getTitle(std::string name) const {
    return ((_showTitle ? "" : "##") + name).c_str();
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
    return  ImPlot::BeginSubplots(getTitle(_name) , _maxSubplots, 1, ImVec2(-1, -1), _flags, calculateRatios().data());
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

const std::string &ChartRenderer::getName() const {
    return _name;
}

void ChartRenderer::setName(const std::string &name) {
    _name = name;
}

