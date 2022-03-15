//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeSubplotRenderer.h"
#include "VolumeData.h"
#include "VolumeRenderer.h"
#include "../../Helpers/PlotHelper.h"
#include "DataSeriesRenderer.h"
#include "fmt/format.h"

#define dataHist (*_ticker->getBarHistory())

VolumeSubplotRenderer::VolumeSubplotRenderer(Ticker *ticker) : SubplotRenderer(ticker) {
    _title = "Volume";
    setFlags(ImPlotFlags_NoMenus);
    addVolumeItem();
}

void VolumeSubplotRenderer::addVolumeItem() {//Add Volume Item
    std::__1::shared_ptr<VolumeData> volume = std::__1::make_unique<VolumeData>(_ticker);
    volume->setPriority(1);
    std::__1::shared_ptr<VolumeRenderer> volumeR = std::__1::make_unique<VolumeRenderer>(_ticker->getContext(), volume.get());
    items.push_back(volumeR);
}


void VolumeSubplotRenderer::onPreRender() {}

void VolumeSubplotRenderer::onSetupPlot() {

    ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time,ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
    ImPlot::SetupAxisLimits(ImAxis_X1, _ticker->getRenderRange().startTime,_ticker->getRenderRange().endTime);
    ImPlot::SetupAxisFormat(ImAxis_Y1, PlotHelper::VolumeFormatter);
    ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = _ticker->getZoomOutMax();

}

void VolumeSubplotRenderer::onPostRender() {}

void VolumeSubplotRenderer::onRender() {
    SubplotRenderer::onRender(); //LV: calling Superclass, right?
    onTooltipRender();

}

void VolumeSubplotRenderer::onTooltipRender() {//TICKER TOOL TIP ##################

    ImDrawList* drawList =  ImPlot::GetPlotDrawList();
    const double candleWidth = _ticker->getSymbol()->getTimeIntervalInMinutes() * 60;

    const bool hovered = ImPlot::IsSubplotsHovered();
    if (hovered) {
        ImPlotPoint mouse   = ImPlot::GetPlotMousePos();
        mouse.x             = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(mouse.x), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
        //vertical line
        float  tool_l       = ImPlot::PlotToPixels(mouse.x - candleWidth/2, mouse.y).x;
        float  tool_r       = ImPlot::PlotToPixels(mouse.x + candleWidth/2, mouse.y).x;
        float  tool_t       = ImPlot::GetPlotPos().y;
        float  tool_b       = tool_t + ImPlot::GetPlotSize().y;
        ImPlot::PushPlotClipRect();
        drawList->AddRectFilled(ImVec2(tool_l, tool_t), ImVec2(tool_r, tool_b), IM_COL32(128,128,128,64));
        ImPlot::PopPlotClipRect();

        // find mouse location index
        int idx = PlotHelper::BinarySearch(dataHist.getData(TIME_S).data(), 0, dataHist.size(), mouse.x);

        // render tool tip (won't be affected by plot clip rect)
        if (ImPlot::IsPlotHovered() && idx != -1) {
            ImGui::BeginTooltip();
            char buff[32];
            ImPlot::FormatDate(ImPlotTime::FromDouble(dataHist.getData(TIME_S)[idx]), buff, 32, ImPlotDateFmt_DayMoYr, ImPlot::GetStyle().UseISO8601);
            ImGui::Text("Date:");   ImGui::SameLine(60); ImGui::Text("%s",  buff);
            ImGui::Text("Open:");   ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(OPEN)[idx]);
            ImGui::Text("Close:");  ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(CLOSE)[idx]);
            ImGui::Text("High:");   ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(HIGH)[idx]);
            ImGui::Text("Low:");    ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(LOW)[idx]);
            ImGui::Text("Volume:"); ImGui::SameLine(60); ImGui::Text("%s", fmt::format(std::locale("en_US.UTF-8"),"{:L}", (int)(dataHist.getData(
                    VOLUME)[idx])).c_str());
            ImGui::EndTooltip();
        }
    }
}

