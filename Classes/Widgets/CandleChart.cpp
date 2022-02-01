//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "CandleChart.h"
#include "../Editor.h"
#include <fmt/format.h>
#include "iostream"

#define dataHist (*_ticker->getBarHistory())

CandleChart::CandleChart(Context* context, Ticker* ticker) : Widget(context)
{
    _title                  = "Candle ChartView";
    _is_window              = false;
    _ticker = ticker;

    ImPlot::FormatDate(_t1,_t1_str,32,ImPlotDateFmt_DayMoYr,true);
    ImPlot::FormatDate(_t2,_t2_str,32,ImPlotDateFmt_DayMoYr,true);

    _lastIdxX = _ticker->getBarHistory()->size() - 1;
}

void CandleChart::updateVisible(float dt) {
    Widget::updateVisible(dt);
    render(dt);
}

std::vector<float> CandleChart::calculateRatios() {

    std::vector<float> ratios;

    ratios.push_back(5);

    for (int i = 0; i < getContext()->getSubplotIndicatorsCount(); i++) {
        ratios.push_back(2);
    }

    ratios.push_back(3);

    while (ratios.size() < getContext()->getSubplotIndicatorsCount() + _maxSubplots) {
        ratios.push_back(0);
    }

    return ratios;
}

void CandleChart::render(float dt)
{
    if(!getContext()->getShouldRender()) return;
    if(_ticker->getBarHistory()->size() <= 0) return;


    static ImVec4 bull_color(0.5,1,0,1);
    static ImVec4 bear_color(1,0,0.5,1);

    _t1 = ImPlot::AddTime(_t2, ImPlotTimeUnit_Yr, -1);

    const double candleWidth = _ticker->getSymbol()->getTimeIntervalInMinutes() * 60;

    std::vector<float> ratios = calculateRatios();

    bool forceChangeMax = false;
    double movedMin, movedMax;

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 16);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab,Editor::broker_yellow_active);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,Editor::broker_yellow);
    ImGui::PushStyleColor(ImGuiCol_FrameBg,Editor::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_light_grey);

    if(ImGui::SliderFloat("##Positioner",&_positionerValue,0.000f,1.000f,"%.3f")){

        int posIdxMax = int((dataHist.size() - 1)*_positionerValue);
        int posIdxMin = posIdxMax - getContext()->getMaxBarsToRender() < 0 ? 0 : posIdxMax - getContext()->getMaxBarsToRender();

        movedMin = dataHist.getData(BarDataType::TIME)[posIdxMin];
        movedMax= dataHist.getData(BarDataType::TIME)[posIdxMax];

        forceChangeMax =  true;
    }
    else{
        //update postioner
        float posPercent = float(_lastIdxX+1)/dataHist.size();
        _positionerValue = posPercent;
    }

    ImGui::PopStyleColor(5);

    if(ImPlot::BeginSubplots("##Subplots",_maxSubplots,1,ImVec2(-1,-1),ImPlotSubplotFlags_LinkCols,ratios.data())){

        int flagsOHLC;
        flagsOHLC |= ImPlotFlags_NoMenus;
//        if(getContext()->isSimulating())
//            flagsOHLC |= ImPlotFlags_NoInputs;


        int numberOfBarsToRender = _ticker->getBarHistory()->size() > getContext()->getMaxBarsToRender() ? getContext()->getMaxBarsToRender() : _ticker->getBarHistory()->size();
        int lastIdxToPlot = _lastIdxX - numberOfBarsToRender  < 0  ? 0 :  _lastIdxX - numberOfBarsToRender ;


        if (ImPlot::BeginPlot("##OHLC",ImVec2(-1,0),flagsOHLC))
        {

            ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time|ImPlotAxisFlags_NoTickLabels,
                              ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
            ImPlot::SetupAxisLimits(ImAxis_X1, dataHist.getData(BarDataType::TIME)[lastIdxToPlot],
                                    dataHist.getData(BarDataType::TIME)[_lastIdxX],BarDataType::TIME);
            ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = getContext()->getZoomOutMax();

            if(forceChangeMax) {
                ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetMin(movedMin);
                ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetMax(movedMax);
            }

//            if simulating move the x axis
            if(getContext()->isSimulating()) {
                 _ticker->getBarHistory()->size() > getContext()->getMaxBarsToRender() ? getContext()->getMaxBarsToRender() : _ticker->getBarHistory()->size();
                double barsInTime = numberOfBarsToRender * 60 * _ticker->getSymbol()->getTimeIntervalInMinutes();
                double currentTime = dataHist(0,BarDataType::TIME);
                ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(currentTime - barsInTime, currentTime);
            }

            ImDrawList* drawList =  ImPlot::GetPlotDrawList();

            if (ImPlot::BeginItem("OHLC")) {
                // override legend icon color
                ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(bull_color);

                // fit data on screen even when zooming
                if (ImPlot::FitThisFrame()) {
                    for (int i = lastIdxToPlot; i <= _lastIdxX; ++i) {
                        ImPlot::FitPoint(ImPlotPoint(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::LOW)[i]));
                        ImPlot::FitPoint(ImPlotPoint(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::HIGH)[i]));
                    }
                }

                for (int i = lastIdxToPlot; i <= _lastIdxX; i++) {
                    ImU32 color = ImGui::GetColorU32(dataHist.getData(BarDataType::OPEN)[i] > dataHist.getData(BarDataType::CLOSE)[i] ? bear_color : bull_color);
                    ImVec2 openPos = ImPlot::PlotToPixels(dataHist.getData(BarDataType::TIME)[i] - candleWidth / 2, dataHist.getData(BarDataType::OPEN)[i]);
                    ImVec2 closePos = ImPlot::PlotToPixels(dataHist.getData(BarDataType::TIME)[i] + candleWidth / 2, dataHist.getData(BarDataType::CLOSE)[i]);
                    drawList->AddRectFilled(openPos, closePos, color);

                    ImVec2 lowPos = ImPlot::PlotToPixels(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::LOW)[i]);
                    ImVec2 highPos = ImPlot::PlotToPixels(dataHist.getData(BarDataType::TIME)[i], dataHist.getData(BarDataType::HIGH)[i]);
                    drawList->AddLine(lowPos, highPos, color, ImMax(1.0f, (closePos.x - openPos.x) / 10.0f));
                }

                //plot tag at the last candle on screen
                ImPlotRect bnds = ImPlot::GetPlotLimits();
//                        double x = ImPlot::RoundTime(ImPlotTime::FromDouble(bnds.X.Max), ImPlotTimeUnit_Hr).ToDouble();
                double minX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Min), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
                double maxX = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Max), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();

                int lastIdx = dataHist.size() - 1;
                int maxX_idx = PlotHelper::BinarySearch<double>(dataHist.getData(BarDataType::TIME).data(), 0, lastIdx, maxX);
                if (maxX_idx == -1)
                    maxX_idx = lastIdx;

                _lastIdxX = maxX_idx;

                //update ticker range #############
                double startTime = minX;
                double endTime = maxX;

                if (startTime <  dataHist.getData(BarDataType::TIME).front()) startTime = dataHist.getData(BarDataType::TIME).front();
                if (endTime >  dataHist.getData(BarDataType::TIME).back()) endTime = dataHist.getData(BarDataType::TIME).back();

                if (startTime >  dataHist.getData(BarDataType::TIME).back()) startTime = dataHist.getData(BarDataType::TIME).front();
                if (endTime <  dataHist.getData(BarDataType::TIME).front()) endTime = dataHist.getData(BarDataType::TIME).back();

                getContext()->updateRenderRange(startTime,endTime);
                //######################################


                double close_val = dataHist.getData(BarDataType::CLOSE)[maxX_idx];
                double open_val =  dataHist.getData(BarDataType::OPEN)[maxX_idx];

                ImPlot::TagY(close_val, open_val < close_val ? bull_color : bear_color);


                //cross dashed lines
                const bool hovered = ImPlot::IsSubplotsHovered();
                if (hovered) {
                    //vertical dashed line
                    double top = ImPlot::PixelsToPlot(ImPlot::GetPlotPos()).y;
                    double bottom = ImPlot::PixelsToPlot(ImPlot::GetPlotPos() + ImPlot::GetPlotSize()).y;

                    double sizeY = bottom - top;
                    int steps = 51;
                    double step = sizeY/steps;

                    ImPlotPoint mouse   = ImPlot::GetPlotMousePos();
                    for(int i = 0; i < steps; i+=2) {
                        ImVec2 topPos = ImPlot::PlotToPixels(mouse.x,top + i*step);
                        ImVec2 bottomPos = ImPlot::PlotToPixels(mouse.x,top + (i+1) * step);
                        drawList->AddLine(topPos, bottomPos, IM_COL32(128, 128, 128, 64), 2.0f);
                    }

                    //horizontal dashed line
                    double tool_l_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos()).x;
                    double tool_r_h = ImPlot::PixelsToPlot(ImPlot::GetPlotPos() + ImPlot::GetPlotSize()).x;

                    double sizeX = tool_r_h - tool_l_h;
                    steps = 101;
                    step = sizeX/steps;

                    for(int i = 0; i < steps; i+=2) {
                        ImVec2 leftPos = ImPlot::PlotToPixels(tool_l_h + i*step, mouse.y);
                        ImVec2 rightPos = ImPlot::PlotToPixels(tool_l_h + (i+1) * step, mouse.y);
                        drawList->AddLine(leftPos, rightPos, IM_COL32(128, 128, 128, 64), 2.0f);
                    }

                    ImPlot::TagY(mouse.y, ImVec4(1,1,1,0.5));
//                            ImPlot::TagX(mouse.x, ImVec4(1,1,1,0.5));

                }
                //#################################

                ImPlot::EndItem();
            }

            //plot candle indicators
            getContext()->plotIndicators();
            getContext()->plotStrategy();

            //allow candles plot area to be a DRAG AND DROP target ##
            if (ImPlot::BeginDragDropTargetPlot()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID)) {
                    //indice of dragged item
                    int i = *(int*)payload->Data;

                    puts("AGORA é a hora de plotar!!!");
                    getContext()->loadIndicator(IndicatorsView::CandleIndicatorsTypes(i), true);
                }
                ImPlot::EndDragDropTarget();
            }
            //######################################################
            ImPlot::EndPlot();
        }

        //plot different views indicators
        getContext()->plotSubplotIndicators();

        if (ImPlot::BeginPlot("##Volume")) {

            ImDrawList* drawList =  ImPlot::GetPlotDrawList();

            ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time,ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
            ImPlot::SetupAxisLimits(ImAxis_X1, dataHist.getData(BarDataType::TIME)[lastIdxToPlot], dataHist.getData(BarDataType::TIME)[_lastIdxX],BarDataType::TIME);
            ImPlot::SetupAxisFormat(ImAxis_Y1, PlotHelper::VolumeFormatter);
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = getContext()->getZoomOutMax();


            auto color = ImVec4(1.f,0.75f,0.25f,1);
            ImPlot::SetNextFillStyle(color);
            int plotSize = _lastIdxX - lastIdxToPlot + 1;
            ImPlot::PlotBars("Volume",&dataHist.getData(BarDataType::TIME)[lastIdxToPlot],&dataHist.getData(BarDataType::VOLUME)[lastIdxToPlot],plotSize, candleWidth*0.5);

            //TICKER TOOL TIP ##################
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
                int idx = PlotHelper::BinarySearch(dataHist.getData(BarDataType::TIME).data(), 0, dataHist.size(), mouse.x);

                // render tool tip (won't be affected by plot clip rect)
                if (ImPlot::IsPlotHovered() && idx != -1) {
                    ImGui::BeginTooltip();
                    char buff[32];
                    ImPlot::FormatDate(ImPlotTime::FromDouble(dataHist.getData(BarDataType::TIME)[idx]),buff,32,ImPlotDateFmt_DayMoYr,ImPlot::GetStyle().UseISO8601);
                    ImGui::Text("Date:");   ImGui::SameLine(60); ImGui::Text("%s",  buff);
                    ImGui::Text("Open:");   ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(BarDataType::OPEN)[idx]);
                    ImGui::Text("Close:");  ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(BarDataType::CLOSE)[idx]);
                    ImGui::Text("High:");   ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(BarDataType::HIGH)[idx]);
                    ImGui::Text("Low:");    ImGui::SameLine(60); ImGui::Text("$%.2f", dataHist.getData(BarDataType::LOW)[idx]);
                    ImGui::Text("Volume:"); ImGui::SameLine(60); ImGui::Text(fmt::format(std::locale("en_US.UTF-8"),"{:L}", (int)(dataHist.getData(BarDataType::VOLUME)[idx])).c_str());
                    ImGui::EndTooltip();
                }
            }
            //#################################
            ImPlot::EndPlot();
        }

        ImPlot::EndSubplots();
    }
}
