//
// Created by Arthur Abel Motelevicz on 29/12/21.
//

#include "TestStrategy.h"
#include "../../Contexts/Context.h"


TestStrategy::TestStrategy(Ticker *ticker) : Strategy(ticker) {
//    _smaSlow = SMA(ticker);
//    _smaFast = SMA(ticker);
//
//    _smaSlow.setAverageSize(24);
//    _smaFast.setAverageSize(9);

//    ticker->addTickable(&_smaFast);
//    ticker->addTickable(&_smaSlow);
}

void TestStrategy::rule() {
    Strategy::rule();

    if(_isPositioned) return;

    auto arrSMA = _ticker->getContext()->getIndicator<SMA>();
    if(arrSMA.empty() || arrSMA.size() <= 1) return;

    SMA _smaSlow = *arrSMA[0];
    SMA _smaFast = *arrSMA[1];

    std::cout << "Slow: " << _smaSlow.getAverageSize() << std::endl;
    std::cout << "Fast: " << _smaFast.getAverageSize() << std::endl;

    if(_smaSlow.size() > 1 && _smaFast.size() > 1){
        //when the slow cross up the fast -> should short
        bool crossUp = _smaSlow[0] > _smaFast[0] && _smaSlow[1] < _smaFast[1];

        //when the slow cross down the fast -> should long
        bool crossDown =_smaSlow[0] < _smaFast[0] && _smaSlow[1] > _smaFast[1];

        if(crossUp) {
            auto id = openPosition(true);
            _isPositioned = true;
        }
        else if(crossDown) {
            auto id = openPosition(false);
            _isPositioned = true;
        }

    }

    return;

    if(barHist.size() < 5) return;

    double fifthPrice   = barHist[4].close;
    double fourthPrice  = barHist[3].close;
    double thirdPrice   = barHist[2].close;
    double secondPrice  = barHist[1].close;
    double lastPrice    = barHist[0].close;

    if( fifthPrice < fourthPrice &&
        fourthPrice < thirdPrice &&
        thirdPrice < secondPrice &&
        secondPrice < lastPrice){

        auto id = openPosition(false);
        _isPositioned = true;
    }

    if( fifthPrice > fourthPrice &&
        fourthPrice > thirdPrice &&
        thirdPrice > secondPrice &&
        secondPrice > lastPrice){

        auto id = openPosition(true);
        _isPositioned = true;
    }
}

void TestStrategy::checkTarget(Strategy::Position &pos) {
    Strategy::checkTarget(pos);

    double lastPrice = pos.outPrice;
    double deltaProfit = _targetPercent*pos.inPrice - pos.inPrice;
    double deltaLastPrice = pos.isShorting ? pos.inPrice - lastPrice : lastPrice - pos.inPrice;

    if( deltaLastPrice >= deltaProfit || deltaLastPrice <= -deltaProfit) {
        closePosition(pos.id);
        _isPositioned = false;
    }

}

void TestStrategy::render() {
    Strategy::render();
}

