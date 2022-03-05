//
// Created by Luiz Veloso on 28/02/22.
//

#ifndef BROKERAPP_INDICATORDATA_H
#define BROKERAPP_INDICATORDATA_H


#include "IndicatorTickable.h"

template<typename M, int N = 1>
class IndicatorData : public IndicatorTickable, public ReversedData<M, N> {
public:
    explicit IndicatorData(Ticker *ticker): IndicatorTickable(ticker) {};
    ~IndicatorData() = default;

    void resetData() {
        IndicatorTickable::reset();//todo: renomear
        ReversedData<M>::clear(); //todo: renomear
    }

    void calculate(BarHistory *barHistory) override = 0;

    //getContext() -> todos os indicadores teriam o getcontext

};



#endif //BROKERAPP_INDICATORDATA_H
