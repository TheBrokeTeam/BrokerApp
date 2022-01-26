//
// Created by Arthur Abel Motelevicz on 31/12/21.
//

#ifndef BROKERAPP_PLOTITEM_H
#define BROKERAPP_PLOTITEM_H

#include <string>
#include <vector>
#include <implot.h>
#include <implot_internal.h>

struct PlotItemInfo{
    int startIndex;
    int size;
};

class Ticker;

class PlotItem {
public:
    PlotItem();
    virtual ~PlotItem();
    virtual void onRender() = 0;
    virtual void resetPlot();
    virtual void onPopupRender();

    void setPlotName(const std::string& name);
    const std::string& getName();
    const std::string& getPlotName();
    const std::string& getId();
    const std::vector<double>& getTime();

    virtual void render();
protected:

    PlotItemInfo getRenderInfo(Ticker* ticker);
    std::string _name{""};
    std::string _plotName{""};
    std::string _plotId{""};
    std::vector<double> _time;

private:
    int getRenderStartIndex(double time);
    int getRenderEndIndex(double time);
    void popupRender();
};


#endif //BROKERAPP_PLOTITEM_H
