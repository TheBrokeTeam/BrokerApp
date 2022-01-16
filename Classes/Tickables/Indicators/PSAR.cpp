//
// Created by Luiz Veloso on 12/01/22.
//

#include "PSAR.h"
#include <iostream>

PSAR::PSAR(Ticker *ticker): Indicator(ticker) {
    setPlotName("PSAR");
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
        _af_step = _af;

        _data.push_back(_sar);
        _time.push_back((*barHistory)[0].time);

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

                _data.push_back(_sar);
                _time.push_back((*barHistory)[0].time);

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
                _data.push_back(_sar);
                _time.push_back((*barHistory)[0].time);

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

                _data.push_back(_sar);
                _time.push_back((*barHistory)[0].time);

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
                _data.push_back(_sar);
                _time.push_back((*barHistory)[0].time);

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
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotScatter(_plotName.c_str(), _time.data(), _data.data(), _time.size());
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

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void PSAR::reset() {
    Indicator::reset();
    _low.clear();
    _high.clear();
    _data.clear();
    _time.clear(); // (lv) pergunta: devo remover isso nos resets tbm?

    //todo: (lv) perguntar pro tato pra entender melhor os resets.
}


PSAR::~PSAR() {

}