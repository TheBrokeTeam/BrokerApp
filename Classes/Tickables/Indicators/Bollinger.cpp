//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#include "Bollinger.h"
#include "../../Tickers/Ticker.h"


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
            mean += (*barHistory)(i,BarDataType::CLOSE) * den;

        //calulate the standard deviation of this
        double den2 = 1.0 / (_averageSize - 1.0);
        double x   = 0;
        for (int i = 0; i < _averageSize; ++i)
            x += ((*barHistory)(i,BarDataType::CLOSE) - mean) * ((*barHistory)(i,BarDataType::CLOSE) - mean) * den2;

        double stdv = sqrt(x);

        double bottom = mean - 2 * stdv;
        double mid = mean;
        double top = mean + 2 * stdv;

        insert(bottom,BollingerDataType::BOTTOM);
        insert(mid,BollingerDataType::MID);
        insert(top,BollingerDataType::TOP);

        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }
}

void Bollinger::resetPlot() {
    Indicator::resetPlot();
    clear();
}

void Bollinger::onRender() {
    //safe check
    if(getData().empty() || size() < 2) return;

    //TODO:: this shaded render commented there is no artifact on it. Get it back.
//    ImPlot::SetNextFillStyle(ImVec4(0.5,0.5,1,1),0.25f);
//    ImPlot::PlotShaded(_code.c_str(),_time.data(),_bollinger_top.data(),_bollinger_bot.data(),_bollinger_mid.size());
//    ImPlot::SetNextLineStyle(ImVec4(0.5,0.5,1,1));

    //TODO:: the custom render was needed to use custom Reversed data type. Maybe it is possible in some way.
    auto color = ImVec4(0.5,0.5,1,0.25);

    ImPlot::GetCurrentItem()->Color = ImGui::GetColorU32(color);

    auto drawList = ImPlot::GetPlotDrawList();

    for(int i = 0; i < _time.size() - 2; i++){

        double p1_x = _time[i];
        double p1_y = _data[i].bottom;

    ImPlot::PlotShaded(_name.c_str(),
                       _time.data(),
                       getData(BollingerDataType::TOP).data(),
                       getData(BollingerDataType::BOTTOM).data(),
                       size());

    ImPlot::SetNextLineStyle(ImVec4(0.5,0.5,1,1));
}

int Bollinger::getAverageSize() {
    return _averageSize;
}

const ImVec4 &Bollinger::getColor() {
    return _color;
}

