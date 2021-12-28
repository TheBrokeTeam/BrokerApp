//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "CandleChart.h"
#include "../Editor.h"
#include "../Contexts/Context.h"
#include <fmt/format.h>
#include "iostream"
#include "../Tickables/SMA.h"

//#include "../Indicators/SMA.h"
//#include "../Helpers/PlotHelper.h"


// convenience struct to manage DND items; do this however you like
//struct MyDndItem {
//    int              Idx;
//    int              Plt;
//    ImAxis           Yax;
//    char             Label[16];
//    ImVector<ImVec2> Data;
//    ImVec4           Color;
//    MyDndItem()        {
//        static int i = 0;
//        Idx = i++;
//        Plt = 0;
//        Yax = ImAxis_Y1;
//        sprintf(Label, "%02d Hz", Idx+1);
//        Color = PlotHelper::RandomColor();
//        Data.reserve(1001);
//        for (int k = 0; k < 1001; ++k) {
//            float t = k * 1.0f / 999;
//            Data.push_back(ImVec2(t, 0.5f + 0.5f * sinf(2*3.14f*t*(Idx+1))));
//        }
//    }
//    void Reset() { Plt = 0; Yax = ImAxis_Y1; }
//};
//
//const int         k_dnd = 20;
//static MyDndItem  dnd[k_dnd];
//static MyDndItem* dndx = NULL; // for plot 2
//static MyDndItem* dndy = NULL; // for plot 2

inline static float randomNumber(){
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

CandleChart::CandleChart(Editor *editor,Ticker* ticker) : Widget(editor), Tickable(ticker)
{
    _title                  = "Candle Chart";
    _is_window              = false;
    _indicatorsView = std::make_unique<Indicators>(editor);

    _indicatorsView->setTrashCallback([this](){
        _indicators.clear();
    });
}

void CandleChart::updateVisible(float dt) {
    Widget::updateVisible(dt);
    render(dt);
}

void CandleChart::render(float dt)
{
    //tests purpose
//    if(_xMaxLast != _xMax && _xMin != _xMinLast)
    getContext()->loadTicker(*_ticker->getSymbol());

    _xMaxLast = _xMax;
    _xMinLast = _xMin;

    //TODO:: this is ugly - find a better way to initialize once the UIItem subclasses
    if(!_initTime)
    {
        ImPlot::FormatDate(_t1,_t1_str,32,ImPlotDateFmt_DayMoYr,true);
        ImPlot::FormatDate(_t2,_t2_str,32,ImPlotDateFmt_DayMoYr,true);
        _initTime = true;

//        _strategy = std::make_unique<TestStrategy>();
//        _ticker->addTickable(_strategy.get());
    }

    if(_barHistory == nullptr || _barHistory->size() <= 0) return;

    static ImVec4 bull_color(0.5,1,0,1);
    static ImVec4 bear_color(1,0,0.5,1);

    _t1 = ImPlot::AddTime(_t2, ImPlotTimeUnit_Yr, -1);

    const double candleWidth = _ticker->getSymbol()->getTimeIntervalInMinutes() * 60;

//    if (ImGui::BeginTabItem(_ticker->getSymbol()->getName().c_str())) {

        if(_showIndicators){
            // showDemoDragAndDrop();
            _indicatorsView->updateVisible(dt);
            ImGui::SameLine();
        }

        static float ratios[] = {2,1};
        if(ImPlot::BeginSubplots("##Subplots",3,1,ImVec2(-1,-1),ImPlotSubplotFlags_LinkCols,ratios)){

            if (ImPlot::BeginPlot("##OHLC"))
            {

                ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time|ImPlotAxisFlags_NoTickLabels,ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
                ImPlot::SetupAxisLimits(ImAxis_X1, barHist[_barHistory->size()-1].time, barHist[0].time);
                ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

                ImDrawList* drawList =  ImPlot::GetPlotDrawList();

                if (ImPlot::BeginItem("OHLC")) {
                    // override legend icon color
                    ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(bull_color);

                    // fit data on screen even when zooming
                    if (ImPlot::FitThisFrame()) {
                        for (int i = 0; i < _barHistory->size(); ++i) {
                            ImPlot::FitPoint(ImPlotPoint(barHist[i].time, barHist[i].low));
                            ImPlot::FitPoint(ImPlotPoint(barHist[i].time, barHist[i].high));
                        }
                    }

                    for (int i = 0; i < _barHistory->size(); i++) {
                        ImU32 color = ImGui::GetColorU32(barHist[i].open > barHist[i].close ? bear_color : bull_color);
                        ImVec2 openPos = ImPlot::PlotToPixels(barHist[i].time - candleWidth / 2, barHist[i].open);
                        ImVec2 closePos = ImPlot::PlotToPixels(barHist[i].time + candleWidth / 2, barHist[i].close);
                        drawList->AddRectFilled(openPos, closePos, color);

                        ImVec2 lowPos = ImPlot::PlotToPixels(barHist[i].time, barHist[i].low);
                        ImVec2 highPos = ImPlot::PlotToPixels(barHist[i].time, barHist[i].high);
                        drawList->AddLine(lowPos, highPos, color, ImMax(1.0f, (closePos.x - openPos.x) / 10.0f));
                    }

                    //plot caindicators
                    plotIndicators();

//                  _strategy->render();


                    //Clamping zoomout tests
                    //plot tag at the last candle on screen
                    ImPlotRect bnds = ImPlot::GetPlotLimits();
//                        double x = ImPlot::RoundTime(ImPlotTime::FromDouble(bnds.X.Max), ImPlotTimeUnit_Hr).ToDouble();
                     _xMin = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Min), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();
                    //Tets render fast
                    _xMax = PlotHelper::RoundTimeMinutes(ImPlotTime::FromDouble(bnds.X.Max), _ticker->getSymbol()->getTimeIntervalInMinutes()).ToDouble();

                    if(_xMax > barHist[0].time)
                        _xMax = barHist[0].time;

                    _ticker->getSymbol()->setRange(_xMin,_xMax);

                    double rangeDelta = _xMax - _xMin;
                    double symbolMaxRange = _ticker->getSymbol()->getMaxRangeSize();
                    if(rangeDelta > symbolMaxRange){

                        ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_xMax - symbolMaxRange,_xMax);
                    }



                    int lastIdx = _barHistory->size() - 1;
                    int lastRenderedBarIdx = PlotHelper::BinarySearch<double>(_barHistory->getTimeData().data(), 0, lastIdx, _xMax);
                    if (lastRenderedBarIdx == -1)
                        lastRenderedBarIdx = lastIdx;

                    double close_val = _barHistory->getData()[lastRenderedBarIdx].close;
                    double open_val =  _barHistory->getData()[lastRenderedBarIdx].open;

                    ImPlot::TagY(close_val, open_val < close_val ? bull_color : bear_color);


                    //TICKER TOOL TIP ##################
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

                //allow candles plot area to be a DRAG AND DROP target ##
                if (ImPlot::BeginDragDropTargetPlot()) {
                    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(Indicators::CANDLE_INDICATORS_DRAG_ID)) {
                        //indice of dragged item
                        int i = *(int*)payload->Data;

                        puts("AGORA é a hora de plotar!!!");
                        loadIndicator(_indicatorsView->getIndicators()[i].type);
                    }
                    ImPlot::EndDragDropTarget();
                }
                //######################################################


                ImPlot::EndPlot();
            }


            if (ImPlot::BeginPlot("##Volume")) {

                ImDrawList* drawList =  ImPlot::GetPlotDrawList();

                ImPlot::SetupAxes(0,0,ImPlotAxisFlags_Time,ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);
                ImPlot::SetupAxisLimits(ImAxis_X1, _barHistory->getTimeData().front(),_barHistory->getTimeData().back());
                ImPlot::SetupAxisFormat(ImAxis_Y1, PlotHelper::VolumeFormatter);

                auto color = ImVec4(1.f,0.75f,0.25f,1);
                ImPlot::SetNextFillStyle(color);
                ImPlot::PlotBars("Volume",_barHistory->getTimeData().data(),_barHistory->getVolumeData().data(),_barHistory->size(), candleWidth*0.5);

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
                    int idx = PlotHelper::BinarySearch(_barHistory->getTimeData().data(), 0, _barHistory->size()-1, mouse.x);

                    // render tool tip (won't be affected by plot clip rect)
                    if (ImPlot::IsPlotHovered() && idx != -1) {
                        ImGui::BeginTooltip();
                        char buff[32];
                        ImPlot::FormatDate(ImPlotTime::FromDouble(barHist[idx].time),buff,32,ImPlotDateFmt_DayMoYr,ImPlot::GetStyle().UseISO8601);
                        ImGui::Text("Date:");   ImGui::SameLine(60); ImGui::Text("%s",  buff);
                        ImGui::Text("Open:");   ImGui::SameLine(60); ImGui::Text("$%.2f", barHist[idx].open);
                        ImGui::Text("Close:");  ImGui::SameLine(60); ImGui::Text("$%.2f", barHist[idx].close);
                        ImGui::Text("High:");   ImGui::SameLine(60); ImGui::Text("$%.2f", barHist[idx].high);
                        ImGui::Text("Low:");    ImGui::SameLine(60); ImGui::Text("$%.2f", barHist[idx].low);
                        ImGui::Text("Volume:"); ImGui::SameLine(60); ImGui::Text(fmt::format(std::locale("en_US.UTF-8"),"{:L}", (int)(barHist[idx].volume)).c_str());
                        ImGui::EndTooltip();
                    }
                }
                //#################################

                ImPlot::EndPlot();
            }

            ImPlot::EndSubplots();
        }
//        ImGui::EndTabItem();
//    }
}

void CandleChart::showIndicators(bool show) {
    _showIndicators = show;
}

void CandleChart::plotIndicators() {
    for(auto& i : _indicators) {
        i->render();
    }

    if(_shouldShowLuizPopup){
        {
            ImGui::OpenPopup("Indicator missing!");
            // Always center this window when appearing
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Indicator missing!", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Hey Luiz, it seems like you are not working too hard.. \nWhat about work on this right now?\n\n");
                ImGui::Separator();

                ImGui::PushStyleColor(ImGuiCol_Button,Editor::broker_light_grey);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_dark_grey);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow);

                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    _shouldShowLuizPopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::PopStyleColor(3);
                ImGui::SetItemDefaultFocus();
                ImGui::EndPopup();
            }
        }
    }
}

void CandleChart::loadIndicator(Indicators::CandleIndicatorsTypes type) {

    switch (type) {
        case Indicators::CandleIndicatorsTypes::MA:
            {
                std::unique_ptr<SMA> sma = std::make_unique<SMA>(_ticker);
                _indicators.push_back(std::move(sma));
                _ticker->addTickable(_indicators.back().get());
            }
            break;
        case Indicators::CandleIndicatorsTypes::EMA:
        case Indicators::CandleIndicatorsTypes::WMA:
        case Indicators::CandleIndicatorsTypes::BOLL:
        case Indicators::CandleIndicatorsTypes::AVL:
        case Indicators::CandleIndicatorsTypes::VWAP:
        case Indicators::CandleIndicatorsTypes::TRIX:
        case Indicators::CandleIndicatorsTypes::SAR :
            _shouldShowLuizPopup = true;
        break;
        default:
            break;
    }
}
// oid CandleChart::addIndicator(const ui_event::AddIndicatorCLicked &event) {
//    std::cout << "Indicator SMA Study: " << event.info.mma << std::endl;
//
//    std::unique_ptr<SMA> sma = std::make_unique<SMA>(event.info.mma);
//    sma->setup("SMA " + std::to_string(event.info.mma));
//
//    sma->setColor(randomNumber(),randomNumber(),randomNumber(),1.0f);
//    sma->setLineWidth(2.0f);
//
//    _indicators.push_back(std::move(sma));
//    _ticker.addTickable(_indicators.back().get());
//}


//void StudyChart::plotIndicators() {
//    for(auto& i : _indicators) {
//        i->render();
//    }
//}

//void StudyChart::onOpen(const Tick &tickData) {
//    Tickable::onOpen(tickData);
//    auto data = _data.getData()[_currentIndex];
//    data.close *= 1.001f;
//    _data.updataDataAt(data,_currentIndex);
//}

//void StudyChart::reset() {
//    Tickable::reset();
//}

//void StudyChart::setSpeed(const ui_event::SliderChanged &event) {
//    _ticker.setSpeed(event);
//}

//void StudyChart::setData(const data_event::DataLoaded &event) {
//    _ticker.setData(event);
//}
//
//void StudyChart::playSimulation(const ui_event::PlaySimulationClicked &event) {
//    _ticker.playSimulation(event);
//}
//
