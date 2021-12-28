//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include <implot_internal.h>

Indicator::Indicator(Ticker *ticker) : Tickable(ticker), Contextualizable(ticker->getContext()) {

}

Indicator::~Indicator() {
    _ys.clear();
    _time.clear();
    _name = "";
}

std::string Indicator::getName() {
    return _name;
}

const std::vector<std::vector<double>>& Indicator::getYs() {
    return _ys;
}

const std::vector<double> &Indicator::getTime(){
    return _time;
}

void Indicator::calculate() {}

void Indicator::render() {

    if(_ys.empty()) return;
    if(_time.empty()) return;

    for(auto& y : _ys )
    {
        ImPlot::SetNextLineStyle(_color,_lineWidth);
        ImPlot::PlotLine(_name.c_str(), _time.data(), y.data(), _time.size());
    }
}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate();
}

void Indicator::reset()
{
    Tickable::reset();
    _ys.clear();
    _time.clear();
}

void Indicator::onLoad(BarHistory *barHistory) {
    Tickable::onLoad(barHistory);
}

void Indicator::setName(const std::string& name) {
    _name = name;
}

//double Indicator::value(int indexBar){
//    return _ys[0][fixedIndex(indexBar)];
//}

//int Indicator::fixedIndex(int indexBar)
//{
//    int fixedIndex = ImMax(0,(int)_ys[0].size() - 1 - indexBar);
//    fixedIndex = ImMin(fixedIndex,(int)_ys[0].size() - 1);
//    return fixedIndex;
//}
