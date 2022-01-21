//
// Created by Luiz Veloso on 12/01/22.
//

#include "PSAR.h"
#include <iostream>
#include "../../Tickers/Ticker.h"


PSAR::PSAR(Ticker *ticker): Indicator(ticker) {
    setPlotName("PSAR");
}

void PSAR::save(bool signal, double sar, double time) {
    PSARData data;

    data.value = sar;
    data.signal = signal;

    _data.push_back(data);
    _time.push_back(time);
}

void PSAR::calculate(BarHistory* barHistory)
{
    if(barHistory->size() != 0) {
        _low.insert(_low.begin(), (*barHistory)[0].low);
        _high.insert(_high.begin(), (*barHistory)[0].high);
    }

    if (_data.empty()) {
        _ep = _high[0];
        _signal = true;
        _sar = _low[0];

        PSAR::save(_signal, _sar, (*barHistory)[0].time);

    } else {
        if (_signal) { // se é long...
            if (_low[0] <= _sar) { // se low é menor que sar, inverte. _sar = _ep
                _signal = false;
                _sar = _ep;
                if (_sar < _high[1]) {
                    _sar = _high[1];
                }

                if (_sar < _high[0]) {
                    _sar = _high[0];
                }

                PSAR::save(_signal, _sar, (*barHistory)[0].time);

                _af = _af_step;
                _ep = _low[0];

                _sar = _sar + _af * (_ep - _sar);

                if (_sar < _high[1]) {
                    _sar = _high[1];
                }
                if (_sar < _high[0]) {
                    _sar = _high[0];
                }

            } else {
                PSAR::save(_signal, _sar, (*barHistory)[0].time);

                if (_high[0] > _ep) {
                    _ep = _high[0];
                    _af += _af_step;
                    if (_af > _amax) {
                        _af = _amax;
                    }
                }
                _sar = _sar + _af * (_ep - _sar);
                if (_sar > _low[1]){
                    _sar = _low[1];
                }

                if (_sar > _low[0]) {
                    _sar = _low[0];
                }
            }
        } else {
            if (_high[0] >= _sar) {
                _signal = true;
                _sar = _ep;
                if (_sar > _low[1]){
                    _sar = _low[1];
                }
                if (_sar > _low[0]) {
                    _sar = _low[0];
                }

                PSAR::save(_signal, _sar, (*barHistory)[0].time);

                _af = _af_step;
                _ep = _high[0];
                _sar = _sar + _af * (_ep - _sar);
                if (_sar > _low[1]){
                    _sar = _low[1];
                }
                if (_sar > _low[0]){
                    _sar = _low[0];
                }

            } else {
                PSAR::save(_signal, _sar, (*barHistory)[0].time);

                if (_low[0] < _ep) {
                    _ep = _low[0];
                    _af += _af_step;
                    if (_af > _amax) {
                        _af = _amax;
                    };
                }
                _sar = _sar + _af * (_ep - _sar);

                if (_sar < _high[1]) {
                    _sar = _high[1];
                }
                if (_sar < _high[0]){
                    _sar = _high[0];
                }
            }
        }
    }
}

void PSAR::onRender() {
    std::vector<double> bottom, top, time_b, time_t;

    for(int i = 0; i < _data.size(); i++){
        if (_data[i].signal) {
            bottom.push_back(_data[i].value);
            time_b.push_back(_time[i]);
        } else {
            top.push_back(_data[i].value);
            time_t.push_back(_time[i]);
        }
    }

    //ImPlot::SetNextLineStyle(_colorTop,_lineWidth);
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, _lineWidth, _colorTop, 1 , _colorTop);
    ImPlot::PlotScatter(_plotName.c_str(), time_t.data(), top.data(), time_t.size());
    //ImPlot::SetNextLineStyle(_colorBottom,_lineWidth);
    ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, _lineWidth, _colorBottom, 1, _colorBottom);
    ImPlot::PlotScatter(_plotName.c_str(), time_b.data(), bottom.data(), time_b.size());

//    for (auto i: _data)
//        std::cout << i << ' ';
}

void PSAR::onPopupRender() {
    if(ImGui::SliderFloat("Accumulation Factor", &_af_step, 0.01, 0.1)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();
    if(ImGui::SliderFloat("Max Factor", &_amax, 0.1, 1.0)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();

    ImGui::ColorEdit4("ColorTop",{&_colorTop.x});
    ImGui::ColorEdit4("ColorBottom",{&_colorBottom.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void PSAR::reset() {
    Indicator::reset();
    _af = _af_step;
    _low.clear();
    _high.clear();
    _data.clear();
    //reset time on parent class Plot Item
    resetPlot();
}


PSAR::~PSAR() {

}