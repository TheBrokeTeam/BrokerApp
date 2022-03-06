//
// Created by Luiz Veloso on 02/03/22.
//

#ifndef BROKERAPP_CHARTRENDERER_H
#define BROKERAPP_CHARTRENDERER_H

#include <vector>
#include "DataSeriesRenderer.h"
#include "../../Contexts/Context.h"
#include "SubplotRenderer.h"

class ChartRendererDelegate {
    virtual void chartDidScroll(int lastVisibleIndex) = 0;
};

class ChartRenderer: SubplotRendererDelegate {
public:
    explicit ChartRenderer(Ticker *ticker);

    std::vector<std::shared_ptr<SubplotRenderer>> subplots;

    void subplotDidScroll(int startIndex, int endIndex, SubplotRenderer *sender) override;

    void setDelegate(ChartRendererDelegate *delegate);

    void render();
//    void updateVisible(float dt); //todo: nao precisa ser widget. precisa disso mesmo assim?

    virtual void onPreRender();
    bool onBeginRender();
    virtual void onRender();
    static void onEndRender();
    virtual void onPostRender();

    bool shouldRender = true;
    int getLastIdxX() const;
    int getLastIdxToPlot() const;
    void addPlotToChart(std::shared_ptr<SubplotRenderer> subplot);
    void removePlotFromChart(std::shared_ptr<SubplotRenderer> subplot);
    const std::string &getName() const;

    void setName(const std::string &name);

    Ticker *_ticker{nullptr};
    void updateRenderInterval(int startIndex, int endIndex);

protected:
    std::string _name;
    RenderInterval _renderInterval = RenderInterval();

private:
    ChartRendererDelegate  *_delegate{};
    char _t1_str[32]{};
    char _t2_str[32]{};
    ImPlotTime _t1;
    ImPlotTime _t2;

    std::vector<float> calculateRatios();
    int _maxSubplots = 10;

    //MARK: Slider stuff
    bool forceChangeMax = false;
    double movedMin{}, movedMax{};
    const int _lastIdxX = 0;
    const int _lastIdxToPlot = 0;
    float _positionerValue = 1.0f;
    bool _forceChangeMax = false;
    double _movedMin = 0, _movedMax = 0;
    void setupSlider();


    ImPlotSubplotFlags getFlags() const;
    void setFlags(ImPlotSubplotFlags flags);
    bool _showTitle = false;
    ImPlotSubplotFlags _flags = ImPlotSubplotFlags_LinkCols;

    const char* getTitle(std::string name) const;
};


#endif //BROKERAPP_CHARTRENDERER_H
