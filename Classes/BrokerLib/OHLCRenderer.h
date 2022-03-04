//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_OHLCRENDERER_H
#define BROKERAPP_OHLCRENDERER_H



#include "DataSeriesRenderer.h"
#include "DataSeriesRendererImgui.h"
#include "OHLCData.h"
#include <implot.h>
#include <implot_internal.h>
#include "BrokerColorsImgui.h"
#include "../Tickers/Ticker.h"

class OHLCRenderer : public DataSeriesRendererImgui {
public:
    OHLCRenderer(Context *context, OHLCData *data);

    ~OHLCRenderer();

    void onRender() override;
    void onPopupRender() override;

protected:
    float _lineWidth = 2.0f;
    OHLCData* _data{};
};



#endif //BROKERAPP_OHLCRENDERER_H
