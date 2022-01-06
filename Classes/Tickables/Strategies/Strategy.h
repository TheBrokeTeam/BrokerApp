//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_STRATEGY_H
#define BROKERAPP_STRATEGY_H

#include "../Tickable.h"
#include "../../Widgets/PlotItem/PlotItem.h"

class Strategy: public Tickable, public PlotItem{
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

    //called when simulation ends
    void onFinish();

    virtual std::string openPosition(bool shorting);
    virtual bool closePosition(const std::string &posId);

    virtual void rule();
    virtual void checkTarget(Strategy::Position &pos);

    double getProfit();

    const std::vector<Position>& getClosedPositions();

    //testing profit and losses
    std::vector<double> profitHistory;
    std::vector<double> lossesHistory;
    std::vector<double> time;
    double drawDownMax = 0;
    double profitMax = 0;
    Ticker* getTicker();

    virtual void onRender() override;

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
