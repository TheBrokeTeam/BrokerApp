//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#include "Bollinger.h"

Bollinger::Bollinger (Ticker *ticker): Indicator(ticker) {
    setPlotName("BOLL");
}

void Bollinger::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _averageSize) {

        //calculate the mean of the last <averagesize>
        double mean = 0;
        double den = 1.0 / _averageSize;
        for (int i = 0; i < _averageSize; ++i)
            mean += (*barHistory)[i].close * den;

        //calulate the standard deviation of this
        double den2 = 1.0 / (_averageSize - 1.0);
        double x   = 0;
        for (int i = 0; i < _averageSize; ++i)
            x += ((*barHistory)[i].close - mean) * ((*barHistory)[i].close - mean) * den2;

        double stdv = sqrt(x);

        BollingerData data;

        data.bottom = mean - 2 * stdv;
        data.mid = mean;
        data.top = mean + 2 * stdv;

        _data.push_back(data);

        _time.push_back((*barHistory)[0].time);
    }
}

void Bollinger::resetPlot() {
    Indicator::resetPlot();
    _data.clear();
}

void Bollinger::onRender() {
    //safe check
    if(_data.empty() || _data.size() < 2) return;

    //TODO:: this shaded render commented there is no artifact on it. Get it back.
//    ImPlot::SetNextFillStyle(ImVec4(0.5,0.5,1,1),0.25f);
//    ImPlot::PlotShaded(_name.c_str(),_time.data(),_bollinger_top.data(),_bollinger_bot.data(),_bollinger_mid.size());
//    ImPlot::SetNextLineStyle(ImVec4(0.5,0.5,1,1));

    //TODO:: the custom render was needed to use custom Reversed data type. Maybe it is possible in some way.
    auto color = ImVec4(0.5,0.5,1,0.25);

    ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(color);

    auto drawList = ImPlot::GetPlotDrawList();

    for(int i = 0; i < _time.size() - 2; i++){

        double p1_x = _time[i];
        double p1_y = _data[i].bottom;

        double p2_x = _time[i];
        double p2_y = _data[i].top;

        double p3_x = _time[i+1];
        double p3_y = _data[i+1].top;

        double p4_x = _time[i+1];
        double p4_y = _data[i+1].bottom;

        ImVec2 p1 = ImPlot::PlotToPixels(p1_x, p1_y);
        ImVec2 p2 = ImPlot::PlotToPixels(p2_x, p2_y);
        ImVec2 p3 = ImPlot::PlotToPixels(p3_x, p3_y);
        ImVec2 p4 = ImPlot::PlotToPixels(p4_x, p4_y);

        ImU32 color32 = ImGui::GetColorU32(color);

        drawList->AddTriangleFilled(p1,p2,p3,color32);
        drawList->AddTriangleFilled(p1,p3,p4,color32);
    }
}

int Bollinger::getAverageSize() {
    return _averageSize;
}

