//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_INDICATOR_H
#define BROKERAPP_INDICATOR_H

#include <vector>
#include <string>
#include "../Tickable.h"

class Indicator : public Tickable , public ReversedData<double> {
public:
    Indicator(Ticker* ticker);
    virtual ~Indicator();

    /** For Now calculate will be called at onClose bar */
    virtual void calculate(BarHistory* barHistory);
    virtual void reset() override;

    void setName(const std::string& name);
    std::string getName();

    const std::vector<double> &getTime();

    virtual void render();

    void onClose(BarHistory* barHistory) override;
    virtual void onLoad(BarHistory* barHistory) override;

protected:
    std::string _name{""};
    std::vector<double> _time;
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
private:
};

#endif //BROKERAPP_INDICATOR_H
