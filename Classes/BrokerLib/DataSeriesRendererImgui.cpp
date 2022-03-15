//
// Created by Luiz Veloso on 27/02/22.
//

#include "DataSeriesRendererImgui.h"
#include "implot.h"

DataSeriesRendererImgui::DataSeriesRendererImgui(Context *context): DataSeriesRenderer(context) {}



bool DataSeriesRendererImgui::onPreRender() {
    return ImPlot::BeginItem(_plotName.c_str());
}

void DataSeriesRendererImgui::onPostRender() {
    ImPlot::EndItem();
}

const ImVec4 &DataSeriesRendererImgui::getColor() {
    return _color;
}

void DataSeriesRendererImgui::setColor(ImVec4 &color) {
    _color = color;
}

void DataSeriesRendererImgui::popupRender() {
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

//void DataSeriesRendererImgui::onRender() {
//
//}
//
//void DataSeriesRendererImgui::onPopupRender() {
//
//}