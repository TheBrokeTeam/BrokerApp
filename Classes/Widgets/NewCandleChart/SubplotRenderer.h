//
// Created by Luiz Veloso on 02/03/22.
//

#ifndef BROKERAPP_SUBPLOTRENDERER_H
#define BROKERAPP_SUBPLOTRENDERER_H

#include <vector>
#include "DataSeriesRenderer.h"
#include "implot/implot.h"
#include "implot/implot_internal.h"
#include "../../Tickers/Ticker.h"
#include "SubplotRendererDelegate.h"

class SubplotRendererDelegate;

class SubplotRenderer {
public:
    std::vector<std::shared_ptr<DataSeriesRenderer>> items;
    SubplotRendererDelegate *delegate;
    explicit SubplotRenderer(Ticker *ticker);
    void addItemToPlot(std::shared_ptr<DataSeriesRenderer> item);
    void removeItemFromPlot(std::shared_ptr<DataSeriesRenderer> item);

    void render();
    const char* getTitle(std::string name) const;


    ImPlotSubplotFlags getFlags() const;
    void setFlags(ImPlotSubplotFlags flags);

    void updateRenderInterval(int startIndex, int endIndex);

protected:
    std::string _title;

    virtual void onPreRender() = 0;
    bool onBeginRender();
    virtual void onSetupPlot() = 0;
    virtual void onRender();
    void onDragDropTarget();
    static void onEndRender();
    virtual void onPostRender() = 0;
    Ticker *_ticker;
    RenderInterval _renderInterval = RenderInterval();

    //Slider stuff
//    const int _lastIdxX = 0;
//    const int _lastIdxToPlot = 0;
//    float _positionValue = 1.0f;
//    bool _forceChangeMax = false;
//    double _movedMin = 0, _movedMax = 0;

private:
    bool _showTitle = false;
    ImPlotSubplotFlags _flags = ImPlotSubplotFlags_None;

};


#endif //BROKERAPP_SUBPLOTRENDERER_H
