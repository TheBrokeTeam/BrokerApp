//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERAPP_PLOTRENDERER_H
#define BROKERAPP_PLOTRENDERER_H

#include <string>
#include <vector>

struct IndicatorRendererInfo{
    int startIndex;
    int size;
};

class Ticker;
class Context;

class PlotRenderer {
public:
    PlotRenderer(Context *context);
    virtual ~PlotRenderer();

    virtual bool onPreRender() = 0;
    virtual void onRender() = 0;
    virtual void onPostRender() = 0;
    virtual void onPopupRender() = 0;
    virtual void onSetupPlot();
    virtual void resetPlot();

    void setPlotName(const std::string& name);
    const std::string& getName();
    const std::string& getPlotName();
    const int getSize();
    const std::string& getId();
    const std::vector<double>& getTime();

    void render();
    bool getIsSubplot();
    void setIsSubplot(bool isSubplot);

protected:
    IndicatorRendererInfo getRenderInfo(Ticker* ticker);
    std::string _name{""};
    std::string _plotName{""};
    std::string _plotId{""};
    std::vector<double> _time;

private:
    int getRenderStartIndex(double time);
    int getRenderEndIndex(double time);
    void popupRender();
    bool _isSubplot = false;
    Context *_context = nullptr;
};


#endif //BROKERAPP_PLOTRENDERER_H
