//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Strategy.h"
#include "../../Helpers/Utils.h"
#include <implot.h>
#include "../../Contexts/Context.h"

Strategy::Strategy(Ticker *ticker) : Tickable(ticker), PlotItem(ticker->getContext()) {
}

int Strategy::BinarySearchPositions(const Position* arr, int l, int r, double time, bool isStart, int maxSize) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if(isStart){
            if(mid - 1 < 0)
                return -1;

            if (arr[mid-1].inTime <= time && arr[mid].inTime >= time)
                return mid;
        }
        else{
            if(mid + 1 >= maxSize)
                return -1;

            if (arr[mid].outTime <= time && arr[mid + 1].outTime >= time )
                return mid;
        }
        if (arr[mid].inTime > time)
            return BinarySearchPositions(arr, l, mid - 1, time, isStart,maxSize);
        return BinarySearchPositions(arr, mid + 1, r, time, isStart,maxSize);
    }
    return -1;
}

void Strategy::onClose(BarHistory* barHistory) {
    Tickable::onClose(barHistory);
    rule();
    checkTarget();
}

void Strategy::onRender() {

    if(_closedPositions.size() <= 1) return;

    std::vector<double> time;
    std::vector<double> y;

    //call finish once if there is opened positions yet
    if(!_ticker->getContext()->isSimulating() &&  !_openedPositions.empty()){
        onFinish();
    }

    int startIdx =  BinarySearchPositions(_closedPositions.data(),
                                          1,
                                          _closedPositions.size() - 1,
                                          _ticker->getRenderRange().startTime,
                                          true,
                                          _closedPositions.size());

    int endIdx =  BinarySearchPositions(_closedPositions.data(),
                                        1,
                                        _closedPositions.size() - 1,
                                        _ticker->getRenderRange().endTime,
                                        false,
                                        _closedPositions.size());

    if(startIdx == -1)
        startIdx = 0;

    if(endIdx == -1)
        endIdx = _closedPositions.size() - 1;

    for(int i = startIdx; i <= endIdx; i++){
        auto c = _closedPositions.at(i);
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

void Strategy::resetPlot() {
    PlotItem::resetPlot();
    _openedPositions.clear();
    _closedPositions.clear();
    _profit = 0;

    profitHistory.clear();
    lossesHistory.clear();
    profitMax = 0;
    drawDownMax = 0;
}

void Strategy::rule() {}

void Strategy::openPosition(const Position &pos) {
    _openedPositions.push_back(pos);
}

void Strategy::closePosition(Position &pos) {
    pos.profit = pos.isShorting ? pos.inPrice - pos.outPrice : pos.outPrice - pos.inPrice;
    _closedPositions.push_back(pos);
    _profit += pos.profit;

    if(_profit > profitMax)
        profitMax = _profit;

    if(_profit < drawDownMax)
        drawDownMax = _profit;

    if(_profit >= 0) {
        profitHistory.push_back(_profit);
        lossesHistory.push_back(0);
    }
    else{
        lossesHistory.push_back(_profit);
        profitHistory.push_back(0);
    }
    _time.push_back(pos.outTime);

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

std::string Strategy::openPosition(bool shorting,double amount) {
    Strategy::Position pos;

    pos.inPrice =  barHist(0,BarDataType::CLOSE);
    pos.outPrice = pos.inPrice;
    pos.id = uuid::generate_uuid_v4();
    pos.isShorting = shorting;
    pos.inTime =  barHist(0,BarDataType::TIME_S);
    pos.outTime =  pos.inTime;
    pos.profit = 0;
    pos.amount = amount;

    openPosition(pos);
    if(_openPositionCallback)
        _openPositionCallback(pos);

    return pos.id;
}

bool Strategy::closePosition(const std::string &posId) {
    for(auto & pos : _openedPositions){
        if(posId == pos.id) {
            closePosition(pos);
            if(_closePositionCallback)
                _closePositionCallback(pos);
            return true;
        }
    }
    return false;
}

void Strategy::checkTarget() {
    for(auto &pos : _openedPositions){
        pos.outTime =  barHist(0,BarDataType::TIME_S);
        pos.outPrice = barHist(0,BarDataType::CLOSE);
        pos.profit = pos.isShorting ? pos.inPrice - pos.outPrice : pos.outPrice - pos.inPrice;

        checkTarget(pos);
    }
}

void Strategy::checkTarget(Strategy::Position &pos) {}


void Strategy::onFinish() {
    for(auto& p : _openedPositions)
        closePosition(p);
}

double Strategy::getProfit() {
    return _profit;
}

Ticker *Strategy::getTicker() {
    return _ticker;
}

const std::vector<Strategy::Position> &Strategy::getClosedPositions() {
    return _closedPositions;
}

const std::vector<Strategy::Position> &Strategy::getOpenedPositions() {
    return _openedPositions;
}

Strategy::~Strategy() {
    _closePositionCallback = nullptr;
    _openPositionCallback = nullptr;
}

void Strategy::reset() {
    Tickable::reset();
    resetPlot();
}

void Strategy::setClosePositionCallback(Strategy::ClosePositionCallback callback) {
    _closePositionCallback = callback;
}

void Strategy::setOpenPositionCallback(Strategy::ClosePositionCallback callback) {
    _openPositionCallback = callback;
}



