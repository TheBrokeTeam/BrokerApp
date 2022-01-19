//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include <implot_internal.h>

#include "../../Helpers/Utils.h"
#include "../../Tickers/Ticker.h"


Indicator::Indicator(Ticker *ticker) : Tickable(ticker) {
    _plotId = uuid::generate_uuid_v4();
    _name = "##" + _plotId;
}

void Indicator::calculate(BarHistory* barHistory) {}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void Indicator::onLoad(BarHistory *barHistory) {
    resetPlot();
    auto tempBarHist = std::make_unique<BarHistory>();
    for(auto&d : (*barHistory).getData()){
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}
void Indicator::resetPlot() {
    PlotItem::resetPlot();
}

Indicator::~Indicator() {}

void Indicator::reset() {
    Tickable::reset();
    resetPlot();
}


