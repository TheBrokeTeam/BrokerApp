//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERAPP_SMARENDERER_H
#define BROKERAPP_SMARENDERER_H

#include "SMAData.h"
#include "PlotRenderer.h"
#include <implot.h>
#include <implot_internal.h>
class SMARenderer : public PlotRenderer {
public:
    SMARenderer(Context* context,SMAData* data);
    ~SMARenderer();

    bool onPreRender() override;
    void onRender() override;
    void onPostRender() override;
    void onPopupRender() override;
//    void onSetupPlot() override;
    void resetPlot() override;
    const ImVec4& getColor();
    void setColor(ImVec4& color);

protected:
    float _lineWidth = 2.0f;
    SMAData* _data;
    ImVec4 _color{1, 1, 1, 1};
};


#endif //BROKERAPP_SMARENDERER_H
