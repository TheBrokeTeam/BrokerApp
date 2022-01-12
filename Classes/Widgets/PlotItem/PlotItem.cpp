//
// Created by Arthur Abel Motelevicz on 31/12/21.
//

#include "PlotItem.h"
#include "../../Helpers/Utils.h"

PlotItem::PlotItem() {
    _plotId = uuid::generate_uuid_v4();
    _plotName = "##" + _plotId;
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
    if (ImPlot::BeginItem(_plotName.c_str())) {
        onRender();
        popupRender();
        ImPlot::EndItem();
    }
}

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

PlotItem::~PlotItem() {
    _name = "";
    _time.clear();
}


