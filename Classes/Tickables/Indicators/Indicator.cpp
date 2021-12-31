//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include <implot_internal.h>

#include "../../Helpers/Utils.h"

Indicator::Indicator(Ticker *ticker) : Tickable(ticker) {
    _id = uuid::generate_uuid_v4();
    _name = "##" + _id;
}

const std::string& Indicator::getName() {
    return _name;
}

const std::string &Indicator::getId() {
    return _id;
}

void Indicator::calculate(BarHistory* barHistory) {}

void Indicator::render() {
    if (ImPlot::BeginItem(_name.c_str())) {
        onRender();
        popupRender();
        ImPlot::EndItem();
    }
}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void Indicator::onLoad(BarHistory *barHistory) {
    reset();
    auto tempBarHist = std::make_unique<BarHistory>();
    for(auto&d : (*barHistory).getData()){
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}

void Indicator::setName(const std::string& name) {
    _name = name + "##" + _id;
}

Indicator::~Indicator() {
    reset();
    _name = "";
}

void Indicator::popupRender() {
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

void Indicator::onPopupRender() {}

void Indicator::reset() {
    _time.clear();
}

const std::vector<double> &Indicator::getTime() {
    return _time;
}

