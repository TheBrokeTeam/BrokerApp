//
// Created by Luiz Veloso on 27/02/22.
//

#include "PlotRendererImgui.h"
#include "implot.h"

PlotRendererImgui::PlotRendererImgui(Context *context): PlotRenderer(context) {}



bool PlotRendererImgui::onPreRender() {
    return ImPlot::BeginItem(_plotName.c_str());
}

void PlotRendererImgui::onPostRender() {
    ImPlot::EndItem();
}

const ImVec4 &PlotRendererImgui::getColor() {
    return _color;
}

void PlotRendererImgui::setColor(ImVec4 &color) {
    _color = color;
}

void PlotRendererImgui::popupRender() {
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

//void PlotRendererImgui::onRender() {
//
//}
//
//void PlotRendererImgui::onPopupRender() {
//
//}