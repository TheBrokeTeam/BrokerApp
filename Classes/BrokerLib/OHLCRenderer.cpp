//
// Created by Luiz Veloso on 04/03/22.
//

#include "OHLCRenderer.h"
#include "implot.h"

OHLCRenderer::OHLCRenderer(Context *context, OHLCData *data): DataSeriesRendererImgui(context) {
    _data = data;
    setPlotName("OHLC");
}

void OHLCRenderer::onRender() {
    ImDrawList* drawList =  ImPlot::GetPlotDrawList();

    //todo: override legend icon color
    ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(BrokerColorsImgui::bull_color);

    //todo: fit data on screen even when zooming
//    if (ImPlot::FitThisFrame()) {
//        for (int i = lastIdxToPlot; i <= _lastIdxX; ++i) {
//            ImPlot::FitPoint(
//                    ImPlotPoint(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::LOW)[i]));
//            ImPlot::FitPoint(
//                    ImPlotPoint(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::HIGH)[i]));
//        }
//    }
    auto renderInfo = getRenderInfo(_data->getTicker(),_data->getTime());
    const double candleWidth = _data->getTicker()->getSymbol()->getTimeIntervalInMinutes() * 60;

    for (int i = renderInfo.startIndex; i <= renderInfo.startIndex + renderInfo.size; i++) {
        ImU32 color = ImGui::GetColorU32(
                _data->getData(BarDataType::OPEN)[i] > _data->getData(BarDataType::CLOSE)[i] ? BrokerColorsImgui::bear_color : BrokerColorsImgui::bull_color);
        ImVec2 openPos = ImPlot::PlotToPixels(_data->getData(BarDataType::TIME)[i] - candleWidth / 2,
                                              _data->getData(BarDataType::OPEN)[i]);
        ImVec2 closePos = ImPlot::PlotToPixels(_data->getData(BarDataType::TIME)[i] + candleWidth / 2,
                                               _data->getData(BarDataType::CLOSE)[i]);
        drawList->AddRectFilled(openPos, closePos, color);

        ImVec2 lowPos = ImPlot::PlotToPixels(_data->getData(BarDataType::TIME)[i],
                                             _data->getData(BarDataType::LOW)[i]);
        ImVec2 highPos = ImPlot::PlotToPixels(_data->getData(BarDataType::TIME)[i],
                                              _data->getData(BarDataType::HIGH)[i]);
        drawList->AddLine(lowPos, highPos, color, ImMax(1.0f, (closePos.x - openPos.x) / 10.0f));
    }

    //todo: plot tag at the last candle on screen
//    ImPlotRect bnds = ImPlot::GetPlotLimits();
////                        double x = ImPlot::RoundTime(ImPlotTime::FromDouble(bnds.X.Max), ImPlotTimeUnit_Hr).ToDouble();
//    double minX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Min),
//                                               _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
//    double maxX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Max),
//                                               _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
//
//    int lastIdx = dataHist.size() - 1;
//    int maxX_idx = PlotHelper::BinarySearch<double>(dataHist.getData(BarDataType::TIME).data(), 0, lastIdx, maxX);
//    if (maxX_idx == -1)
//        maxX_idx = lastIdx;
//
//    _lastIdxX = maxX_idx;

    //todo: update ticker range #############
//    double startTime = minX;
//    double endTime = maxX;
//
//    if (startTime < dataHist.getData(BarDataType::TIME).front())
//        startTime = dataHist.getData(BarDataType::TIME).front();
//    if (endTime > dataHist.getData(BarDataType::TIME).back()) endTime = dataHist.getData(BarDataType::TIME).back();
//
//    if (startTime > dataHist.getData(BarDataType::TIME).back()) startTime = dataHist.getData(BarDataType::TIME).front();
//    if (endTime < dataHist.getData(BarDataType::TIME).front()) endTime = dataHist.getData(BarDataType::TIME).back();
//
//    _ticker->updateRenderRange(startTime, endTime);
    //######################################


//    double close_val = dataHist.getData(BarDataType::CLOSE)[maxX_idx];
//    double open_val = dataHist.getData(BarDataType::OPEN)[maxX_idx];
//
//    ImPlot::TagY(close_val, open_val < close_val ? bull_color : bear_color);
//
//
//    //todo: cross dashed lines
//    const bool hovered = ImPlot::IsSubplotsHovered();
//    if (hovered) {
//        //vertical dashed line
//        double top = ImPlot::PixelsToPlot(ImPlot::GetPlotPos()).y;
//        double bottom = ImPlot::PixelsToPlot(ImPlot::GetPlotPos() + ImPlot::GetPlotSize()).y;
//
//        double sizeY = bottom - top;
//        int steps = 51;
//        double step = sizeY / steps;
//
//        ImPlotPoint mouse = ImPlot::GetPlotMousePos();
//        for (int i = 0; i < steps; i += 2) {
//            ImVec2 topPos = ImPlot::PlotToPixels(mouse.x, top + i * step);
//            ImVec2 bottomPos = ImPlot::PlotToPixels(mouse.x, top + (i + 1) * step);
//            drawList->AddLine(topPos, bottomPos, IM_COL32(128, 128, 128, 64), 2.0f);
//        }
//
//        //horizontal dashed line
//        double tool_l_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos()).x;
//        double tool_r_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos() + ImPlot::GetPlotSize()).x;
//
//        double sizeX = tool_r_h - tool_l_h;
//        steps = 101;
//        step = sizeX / steps;
//
//        for (int i = 0; i < steps; i += 2) {
//            ImVec2 leftPos = ImPlot::PlotToPixels(tool_l_h + i * step, mouse.y);
//            ImVec2 rightPos = ImPlot::PlotToPixels(tool_l_h + (i + 1) * step, mouse.y);
//            drawList->AddLine(leftPos, rightPos, IM_COL32(128, 128, 128, 64), 2.0f);
//        }
//
//        ImPlot::TagY(mouse.y, ImVec4(1, 1, 1, 0.5));
////                            ImPlot::TagX(mouse.x, ImVec4(1,1,1,0.5));
//
//    }

}

void OHLCRenderer::onPopupRender() {

}

OHLCRenderer::~OHLCRenderer() {

}

