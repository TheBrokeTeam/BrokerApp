//
// Created by Luiz Veloso on 02/03/22.
//

#ifndef BROKERAPP_CHARTRENDERER_H
#define BROKERAPP_CHARTRENDERER_H

#include <vector>
#include "DataSeriesRenderer.h"
#include "../../Contexts/Context.h"
#include "SubplotRenderer.h"


class ChartRenderer {
public:
    ChartRenderer(Ticker* ticker);


    std::vector<std::shared_ptr<SubplotRenderer>> subplots;


    void render();
//    void updateVisible(float dt); //todo: nao precisa ser widget. precisa disso mesmo assim?

    void onPreRender();
    bool onBeginRender();

    bool shouldRender = true;
    int getLastIdxX() const;
    int getLastIdxToPlot() const;
    void addPlotToChart(std::shared_ptr<SubplotRenderer> subplot);
    void removePlotFromChart(std::shared_ptr<SubplotRenderer> subplot);
protected:
    std::string _title;

private:
    char _t1_str[32];
    char _t2_str[32];
    static   ImPlotTime _t1;
    ImPlotTime _t2;
    std::vector<float> calculateRatios();
    int _maxSubplots = 10;

    //Slider stuff
    bool forceChangeMax = false;
    double movedMin, movedMax;
    const int _lastIdxX = 0;
    const int _lastIdxToPlot = 0;
    float _positionerValue = 1.0f;
    bool _forceChangeMax = false;
    double _movedMin = 0, _movedMax = 0;
    Ticker* _ticker{nullptr};

    void setupSlider();

    ImPlotSubplotFlags getFlags() const;
    void setFlags(ImPlotSubplotFlags flags);
    bool _showTitle = false;
    ImPlotSubplotFlags _flags = ImPlotSubplotFlags_None;

    const char* getTitle(std::string name) const;
};


#endif //BROKERAPP_CHARTRENDERER_H
