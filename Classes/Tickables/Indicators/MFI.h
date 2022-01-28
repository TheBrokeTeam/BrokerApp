//
// Created by Luiz Veloso on 27/01/22.
//

#ifndef BROKERAPP_MFI_H
#define BROKERAPP_MFI_H


#include "Indicator.h"

class MFI : public Indicator,  public ReversedData<double>{
public:
    explicit MFI(Ticker* ticker);
    ~MFI();
    void calculate(BarHistory* barHistory) override;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;
    void save(bool signal, double sar, double time);
    const ImVec4& getColor();

private:
    ImVec4 _colorTop{175.0/250.0, 50.0/255.0, 50.0/255.0, 1};
    ImVec4 _colorBottom{75.0/255.0, 200.0/255, 75.0/255.0, 1};
    float _lineWidth = 1.5f;
    float _upperBand = 0.8;
    float _lowerBand = 0.2;

    static double calculateTypicalPrice(double low, double high, double close);

    ReversedData<double> _typicalPrice;
    ReversedData<double> _positiveMoneyFlow;
    ReversedData<double> _negativeMoneyFlow;
    int _averageSize = 14;


};



#endif //BROKERAPP_MFI_H
