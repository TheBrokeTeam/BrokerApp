//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include "../../Helpers/Utils.h"

Indicator::Indicator(Ticker *ticker) : Tickable(ticker) {}

std::string Indicator::getName() {
    return _name;
}

const std::vector<double> &Indicator::getTime(){
    return _time;
}

void Indicator::calculate(BarHistory* barHistory) {}

void Indicator::render() {

    if(_data.empty()) return;
    if(_time.empty()) return;

    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_name.c_str(), _time.data(), _data.data(), _time.size());
}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void Indicator::reset()
{
    _data.clear();
    _time.clear();
}

void Indicator::onLoad(BarHistory *barHistory) {
    reset();
    auto tempBarHist = std::make_unique<BarHistory>();
    for(auto&d : barHist.getData()){
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}

void Indicator::setName(const std::string& name) {
    _name = name + "##" + uuid::generate_uuid_v4();
}

Indicator::~Indicator() {
    _data.clear();
    _time.clear();
    _name = "";
}
