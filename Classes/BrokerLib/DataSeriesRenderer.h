//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERAPP_DATASERIESRENDERER_H
#define BROKERAPP_DATASERIESRENDERER_H

#include <string>
#include <vector>
#include "imgui.h"

struct IndicatorRendererInfo{
    int startIndex;
    int size;
};

class Ticker;
class Context;

class DataSeriesRenderer {
public:
    explicit DataSeriesRenderer(Context *context);
    ~DataSeriesRenderer();

    virtual bool onPreRender() = 0;
    virtual void onRender() = 0;
    virtual void onPostRender() = 0;
    virtual void onPopupRender() = 0;
    void onSetupPlot();

    void setPlotName(const std::string& name);
    const std::string& getName();
    const std::string& getPlotName();
    const std::string& getId();


    void render();
    virtual void popupRender() = 0;
    bool getIsSubplot();
    void setIsSubplot(bool isSubplot);

protected:
    static IndicatorRendererInfo getRenderInfo(Ticker* ticker, const std::vector<double>& timeArr);
    std::string _name;
    std::string _plotName;
    std::string _plotId;

private:
    static int getRenderStartIndex(double time,const std::vector<double>& timeArr);
    static int getRenderEndIndex(double time,const std::vector<double>& timeArr);
    bool _isSubplot = false;
    Context *_context = nullptr;
};


#endif //BROKERAPP_DATASERIESRENDERER_H
