//
// Created by Luiz Veloso on 12/01/22.
//

#ifndef BROKERAPP_PSAR_H
#define BROKERAPP_PSAR_H


#include "Indicator.h"
class PSARData{
public:
    bool signal;
    double value;

};

class PSAR : public Indicator,  public ReversedData<PSARData>{
public:
    explicit PSAR(Ticker* ticker);
    ~PSAR();
    void calculate(BarHistory* barHistory) override;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;
    void save(bool signal, double sar, double time);

private:
    ImVec4 _colorTop{1, 1, 1, 1};
    ImVec4 _colorBottom{1, 1, 1, 1};
    float _lineWidth = 0.8f;
    std::vector<double> _low;
    std::vector<double> _high;
    float _af = 0.02;
    float _af_step = 0.02;
    float _amax = 0.20;
    double _ep;
    double _sar;
    bool _signal = true;


};


#endif //BROKERAPP_PSAR_H
