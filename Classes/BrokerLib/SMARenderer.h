//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERAPP_SMARENDERER_H
#define BROKERAPP_SMARENDERER_H

#include "SMAData.h"
#include "PlotRenderer.h"
#include "PlotRendererImgui.h"
#include <implot.h>
#include <implot_internal.h>

class SMARenderer : public PlotRendererImgui {
public:
    SMARenderer(Context *context, SMAData* data);
    ~SMARenderer();

    void onRender() override;
    void onPopupRender() override;

protected:
    float _lineWidth = 2.0f;
    SMAData* _data;
};


#endif //BROKERAPP_SMARENDERER_H
