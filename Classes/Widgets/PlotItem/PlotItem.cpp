//
// Created by Arthur Abel Motelevicz on 31/12/21.
//

#include "PlotItem.h"
#include "../../Helpers/Utils.h"

PlotItem::PlotItem() {
    _id = uuid::generate_uuid_v4();
    _name = "##" + _id;
}

const std::string& PlotItem::getName() {
    return _name;
}

const std::string &PlotItem::getId() {
    return _id;
}

void PlotItem::render() {
    if (ImPlot::BeginItem(_name.c_str())) {
        onRender();
        popupRender();
        ImPlot::EndItem();
    }
}

void PlotItem::setName(const std::string& name) {
    _name = name + "##" + _id;
}

void PlotItem::popupRender() {
    if (ImPlot::BeginLegendPopup(_name.c_str())) {

        const int buffMaxSize = 50;
        static char buff[buffMaxSize] = "DUMMY_NAME";

        for(int i = 0; i < _name.length(); i++ )
        {
            if(i >= buffMaxSize-1)
                break;
            buff[i] = _name.at(i);
        }

        ImGui::SetNextItemWidth(350);
        if (ImGui::InputText("##ID",buff,buffMaxSize,ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_ReadOnly)) {
            _name = buff;
        }

        ImGui::SameLine();

        if(ImGui::Button("Copy ID",ImVec2(100,30))){
            ImGui::SetClipboardText(_name.c_str());
        }

        ImGui::Separator();

        //call the popup to custom controllers on subclasses
        onPopupRender();

        ImPlot::EndLegendPopup();
    }
}


void PlotItem::onPopupRender() {}

void PlotItem::reset() {
    _time.clear();
}

const std::vector<double> &PlotItem::getTime() {
    return _time;
}

PlotItem::~PlotItem() {
    _name = "";
    _time.clear();
}


