//
// Created by Arthur Abel Motelevicz on 29/12/21.
//

#include "TestStrategy.h"

TestStrategy::TestStrategy(Ticker *ticker) : Strategy(ticker) {

}

void TestStrategy::rule() {
    Strategy::rule();

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
    }

    if( fifthPrice > fourthPrice &&
        fourthPrice > thirdPrice &&
        thirdPrice > secondPrice &&
        secondPrice > lastPrice){

        auto id = openPosition(true);
    }
}

void TestStrategy::checkTarget(Strategy::Position &pos) {
    Strategy::checkTarget(pos);

    double lastPrice = barHist[0].close;
    double deltaProfit = _targetPercent*pos.inPrice - pos.inPrice;
    double deltaLastPrice = pos.isShorting ? pos.inPrice - lastPrice : lastPrice - pos.inPrice;

    if( deltaLastPrice >= deltaProfit  || deltaLastPrice <= (-1)*deltaProfit) {
        closePosition(pos.id);
    }
}

