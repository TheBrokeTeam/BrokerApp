//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Symbol.h"

void Symbol::setRange(double start, double end) {
    _range.start = start;
    _range.end = end;
}

Symbol::TimeRange Symbol::getRange() const{
    return _range;
}

double Symbol::getMaxRangeSize() {
    return getTimeIntervalInMinutes()*_maxBarsToRenderOnChart*60;
}
