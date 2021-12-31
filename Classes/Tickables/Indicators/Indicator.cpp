//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Indicator.h"
#include <implot.h>
#include <implot_internal.h>

#include "../../Helpers/Utils.h"

Indicator::Indicator(Ticker *ticker) : Tickable(ticker) {
    _id = uuid::generate_uuid_v4();
    _name = "##" + _id;
}

void Indicator::calculate(BarHistory* barHistory) {}

void Indicator::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void Indicator::onLoad(BarHistory *barHistory) {
    reset();
    auto tempBarHist = std::make_unique<BarHistory>();
    for(auto&d : (*barHistory).getData()){
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}
void Indicator::reset() {
    PlotItem::reset();
}

Indicator::~Indicator() {}


