//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_INDICATOR_H
#define BROKERAPP_INDICATOR_H

#include <vector>
#include <string>
#include "../Tickable.h"
#include <implot.h>
#include <implot_internal.h>

class Indicator : public Tickable {
public:
    Indicator(Ticker* ticker);
    virtual ~Indicator();

    //TODO:: this is a main behavior and need attention
    /** For Now calculate will be called at onClose bar */
    virtual void calculate(BarHistory* barHistory);
    void onClose(BarHistory* barHistory) override;
    void onLoad(BarHistory* barHistory) override;
    void setName(const std::string& name);

    void reset() override;

    const std::string& getName();
    const std::string& getId();
    const std::vector<double> &getTime();

    virtual void onRender() = 0;

    virtual void onPopupRender();
    void render();

protected:
    std::string _name{""};
    std::string _id{""};
    std::vector<double> _time;

private:
    void popupRender();
};

#endif //BROKERAPP_INDICATOR_H
