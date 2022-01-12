//
// Created by Luiz Veloso on 11/01/22.
//

#ifndef BROKERAPP_TRIX_H
#define BROKERAPP_TRIX_H


#include "Indicator.h"

class TRIX : public Indicator,  public ReversedData<double>{
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
    int _smothingSize = 2; // must be <= 1 + _averageSize... it's almost always 2.
    int _averageSize = 14; // must be >= 1
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
    std::vector<double>  priceSequence;
    std::vector<double>  EMA1;
    std::vector<double>  EMA2;
    std::vector<double>  EMA3;
    double calculateEMA(std::vector<double> origin, std::vector<double> destination, int averageSize);


};


#endif //BROKERAPP_TRIX_H
