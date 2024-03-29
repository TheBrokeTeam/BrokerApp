//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Strategy.h"
#include "../../Helpers/Utils.h"
#include <implot.h>
#include "../../Contexts/Context.h"

Strategy::Strategy(Ticker *ticker) : Tickable(ticker) {

}

void Strategy::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    rule();
    checkTarget();
}

void Strategy::render() {
    std::vector<double> time;
    std::vector<double> y;

    if(!_ticker->getContext()->isSimulating() &&  !_openedPositions.empty()){
        onFinish();
    }

    for(auto &c : _closedPositions) {
        time.push_back(c.inTime);
        time.push_back(c.outTime);

        y.push_back(c.inPrice);
        y.push_back(c.outPrice);

        ImPlot::SetNextLineStyle(c.profit > 0 ? _colorPositive : _colorNegative, _lineWidth);
        ImPlot::PlotLine("##Trade", time.data(), y.data(), time.size());

        time.clear();
        y.clear();
    }
}

void Strategy::reset() {
    Tickable::reset();
    _openedPositions.clear();
    _closedPositions.clear();
    _profit = 0;
}

void Strategy::rule() {}

void Strategy::openPosition(const Position &pos) {
    _openedPositions.push_back(pos);
}

void Strategy::closePosition(Position &pos) {
    pos.profit = pos.isShorting ? pos.inPrice - pos.outPrice : pos.outPrice - pos.inPrice;
    _closedPositions.push_back(pos);
    _profit += pos.profit;
    std::cout << "Profit: " << pos.profit << std::endl;
    std::cout << "Total Profit: " << _profit << std::endl;
    removeOpenedPosition(pos);
}

void Strategy::removeOpenedPosition(const Position &pos) {
    for(auto it = _openedPositions.begin(); it != _openedPositions.end() ; it++){
        if(pos.id == (*it).id) {
            _openedPositions.erase(it);
            return;
        }
    }
}

std::string Strategy::openPosition(bool shorting) {
    Strategy::Position pos;
    pos.inPrice =  barHist[0].close;
    pos.outPrice = pos.inPrice;
    pos.id = uuid::generate_uuid_v4();
    pos.isShorting = shorting;
    pos.inTime =  barHist[0].time;
    pos.outTime =  pos.inTime;
    pos.profit = 0;
    openPosition(pos);
    return pos.id;
}

bool Strategy::closePosition(const std::string &posId) {
    for(auto & pos : _openedPositions){
        if(posId == pos.id) {
            closePosition(pos);
            return true;
        }
    }
    return false;
}

void Strategy::checkTarget() {
    for(auto &pos : _openedPositions){
        pos.outTime =  barHist[0].time;
        pos.outPrice = barHist[0].close;;
        checkTarget(pos);
    }
}

void Strategy::checkTarget(Strategy::Position &pos) {}

Strategy::~Strategy() {

}

void Strategy::onFinish() {
    for(auto& p : _openedPositions)
        closePosition(p);
}

