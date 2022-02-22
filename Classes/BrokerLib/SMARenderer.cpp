//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#include "SMARenderer.h"
#include "../Tickers/Ticker.h"
#include "../Contexts/Context.h"

SMARenderer::SMARenderer(Context* context,SMAData* data):PlotRenderer(context){
    _data = data;
};

SMARenderer::~SMARenderer() {}

    bool SMARenderer::onPreRender() {
    return ImPlot::BeginItem(_plotName.c_str());
}

void SMARenderer::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_data->getTicker(),_data->getTime());
    ImPlot::PlotLine(_plotName.c_str(), &_data->getTime()[renderInfo.startIndex], &_data->getData()[renderInfo.startIndex], renderInfo.size);
}
void SMARenderer::onPopupRender()
{
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
         int as = _data->getAverageSize();
         if(ImGui::SliderInt("Average size", &as, 1, 200)){
             _data->reset();
             _data->setAverageSize(as);
             _data->onLoad(_data->getTicker()->getBarHistory());
         }
         ImGui::ColorEdit4("Color",&_color.x);
         ImGui::Separator();
         ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);

        ImPlot::EndLegendPopup();
     }
}


void SMARenderer::onPostRender() {
    ImPlot::EndItem();
}

const ImVec4 &SMARenderer::getColor() {
    return _color;
}

void SMARenderer::setColor(ImVec4 &color) {
    _color = color;
}

