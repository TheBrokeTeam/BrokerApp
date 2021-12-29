//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_STRATEGY_H
#define BROKERAPP_STRATEGY_H

#include "../Tickable.h"

class Strategy: public Tickable{
public:
    struct Position {
        std::string id;
        double inTime;
        double outTime;
        double inPrice;
        double outPrice;
        double profit;
        bool isShorting;
    };

    Strategy(Ticker* ticker);
    virtual ~Strategy();
    void onClose(BarHistory* barHistory) override;
    void reset() override;
    virtual void render();

    //calls this when simulation ends
    void onFinish();

    virtual std::string openPosition(bool shorting);
    virtual bool closePosition(const std::string &posId);

    virtual void rule();
    virtual void checkTarget(Strategy::Position &pos);

protected:
    std::vector<Position> _openedPositions;
    std::vector<Position> _closedPositions;

    double _profit = 0;

private:
    void checkTarget();
    void removeOpenedPosition(const Position& pos);
    void openPosition(const Position& pos);
    void closePosition(Position& pos);
    ImVec4 _colorPositive{0, 0, 1, 1};
    ImVec4 _colorNegative{1, 0, 0, 1};
    float _lineWidth = 1.0f;
};

#endif //BROKERAPP_STRATEGY_H
