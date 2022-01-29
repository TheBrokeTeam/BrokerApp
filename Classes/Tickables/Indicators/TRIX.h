//
// Created by Luiz Veloso on 11/01/22.
//

#ifndef BROKERAPP_TRIX_H
#define BROKERAPP_TRIX_H


#include "Indicator.h"

class TRIX : public Indicator,  public ReversedData<double> {
public:
    explicit TRIX(Ticker* ticker);
    ~TRIX();
    void calculate(BarHistory* barHistory) override;
    void setAverageSize(int size);
    int getAverageSize() const;

    void onRender() override;
    void render() override;

    void onPopupRender() override;
    void reset() override;

private:
    int _averageSize = 14; // must be >= 1
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
    ReversedData<double>  priceSequence;
    ReversedData<double>  EMA1;
    ReversedData<double>  EMA2;
    ReversedData<double>  EMA3;
    double calculateEMA(ReversedData<double>& origin,ReversedData<double>& destination, int averageSize);

};


#endif //BROKERAPP_TRIX_H
