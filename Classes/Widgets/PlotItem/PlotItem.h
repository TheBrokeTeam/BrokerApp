//
// Created by Arthur Abel Motelevicz on 31/12/21.
//

#ifndef BROKERAPP_PLOTITEM_H
#define BROKERAPP_PLOTITEM_H

#include <string>
#include <vector>
#include <implot.h>
#include <implot_internal.h>

class PlotItem {
public:
    PlotItem();
    virtual ~PlotItem();
    virtual void onRender() = 0;
    virtual void reset();
    virtual void onPopupRender();

    void setPlotName(const std::string& name);
    const std::string& getName();
    const std::string& getPlotName();
    const std::string& getId();
    const std::vector<double>& getTime();

    void render();

protected:
    std::string _name{""};
    std::string _plotName{""};
    std::string _plotId{""};
    std::vector<double> _time;

private:
    void popupRender();
};


#endif //BROKERAPP_PLOTITEM_H
