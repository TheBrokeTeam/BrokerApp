//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_BOLLINGER_H
#define BROKERAPP_BOLLINGER_H


#include "Indicator.h"

class Bollinger : public Indicator {
public:
    Bollinger(Ticker* ticker);
    ~Bollinger();
    void calculate(BarHistory* barHistory) override;
    void render() override;
private:
    int _avarageSize = 20;
    std::vector<double> _bollinger_top;
    std::vector<double> _bollinger_mid;
    std::vector<double> _bollinger_bot;

};


#endif //BROKERAPP_BOLLINGER_H
