//
// Created by Arthur Abel Motelevicz on 31/12/21.
//

#include "PlotItem.h"
#include "../../Helpers/Utils.h"
#include "../../Helpers/PlotHelper.h"
#include "../../Tickers/Ticker.h"
#include "../IndicatorsView.h"
#include "../../Contexts/Context.h"


PlotItem::PlotItem(Context *context) {
    _plotId = uuid::generate_uuid_v4();
    _plotName = "##" + _plotId;
    _context = context;
}

const std::string& PlotItem::getName() {
    return _name;
}

const std::string& PlotItem::getPlotName() {
    return _plotName;
}

const std::string &PlotItem::getId() {
    return _plotId;
}




void PlotItem::render() {
    if (_isSubplot) {
        if (ImPlot::BeginPlot(("##"+getPlotName()).c_str())) {
            onSetupPlot();

            onRender();
            popupRender();
            _context->handleDragDrop(this);
            ImPlot::EndPlot();
        }
    } else {
        if (ImPlot::BeginItem(_plotName.c_str())) {
            onRender();
            popupRender();
            _context->handleDragDrop(this);
            ImPlot::EndItem();
        }
    }


}

void PlotItem::onRender(){}

void PlotItem::onSetupPlot(){}

void PlotItem::setPlotName(const std::string& name) {
    _plotName = name + "##" + _plotId;
    _name = name;
}

void PlotItem::popupRender() {
    if (ImPlot::BeginLegendPopup(_plotName.c_str())) {

        const int buffMaxSize = 50;
        static char buff[buffMaxSize] = "";

        for(int i = 0; i < _plotId.length(); i++ )
        {
            if(i >= buffMaxSize-1)
                break;
            buff[i] = _plotId.at(i);
        }

        int flagsID = ImGuiInputTextFlags_CharsUppercase;
//        flagsID |= ImGuiInputTextFlags_ReadOnly;
        flagsID |= ImGuiInputTextFlags_EnterReturnsTrue;

        ImGui::SetNextItemWidth(350);
        if (ImGui::InputText("##ID",buff,buffMaxSize,flagsID)) {
            setPlotName(buff);
        }

        ImGui::SameLine();

        if(ImGui::Button("Copy ID",ImVec2(100,30))){
            ImGui::SetClipboardText(_plotId.c_str());
        }

        ImGui::Separator();

        //call the popup to custom controllers on subclasses
        onPopupRender();

        ImPlot::EndLegendPopup();
    }
}


void PlotItem::onPopupRender() {}

void PlotItem::resetPlot() {
    _time.clear();
}

const std::vector<double> &PlotItem::getTime() {
    return _time;
}

const int PlotItem::getSize() {
    return _time.size();
}

PlotItem::~PlotItem() {
    _name = "";
    _time.clear();
}

int PlotItem::getRenderStartIndex(double time) {
    int startIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(),time);

    if(startIdx == -1)
        startIdx = 0;

    return startIdx;
}

int PlotItem::getRenderEndIndex(double time) {
    int endIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(),time);

    if(endIdx == -1)
        endIdx = _time.size() - 1;

    return endIdx;
}

PlotItemInfo PlotItem::getRenderInfo(Ticker *ticker) {
    PlotItemInfo info;
    info.startIndex = getRenderStartIndex(ticker->getRenderRange().startTime);
    auto endIndex = getRenderEndIndex(ticker->getRenderRange().endTime);
    info.size = endIndex - info.startIndex + 1;
    assert(info.size > 0 && "Info size should not be negative!");
    return  info;
}

bool PlotItem::getIsSubplot() {
    return _isSubplot;
}

void PlotItem::setIsSubplot(bool isSubplot) {
    _isSubplot = isSubplot;
}

