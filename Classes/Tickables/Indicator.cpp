//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include <implot_internal.h>
#include "../Helpers/Utils.h"

Indicator::Indicator(Ticker *ticker) : Tickable(ticker) {

}

Indicator::~Indicator() {
    _data.clear();
    _time.clear();
    _name = "";
}

std::string Indicator::getName() {
    return _name;
}

//const std::vector<std::vector<double>>& Indicator::getYs() {
//    return _data;
//}

const std::vector<double> &Indicator::getTime(){
    return _time;
}

void Indicator::calculate() {}

void Indicator::render() {

    if(_data.empty()) return;
    if(_time.empty()) return;

//    for(auto& y : _data )
//    {
        ImPlot::SetNextLineStyle(_color,_lineWidth);
        ImPlot::PlotLine(_name.c_str(), _time.data(), _data.data(), _time.size());
//    }
}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate();
}

void Indicator::reset()
{
    _data.clear();
    _time.clear();
}

void Indicator::onLoad(BarHistory *barHistory) {
    Tickable::onLoad(barHistory);
}

void Indicator::setName(const std::string& name) {
    _name = name + "##" + uuid::generate_uuid_v4();
}

double Indicator::operator[](int reversedIndex) {
    return 0;
}
