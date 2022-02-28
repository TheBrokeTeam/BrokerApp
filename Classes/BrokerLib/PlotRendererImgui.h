//
// Created by Luiz Veloso on 27/02/22.
//

#ifndef BROKERAPP_PLOTRENDERERIMGUI_H
#define BROKERAPP_PLOTRENDERERIMGUI_H


#include "PlotRenderer.h"
#include "IndicatorTickable.h"
#include <implot.h>
#include <implot_internal.h>

class PlotRendererImgui: public PlotRenderer {
public:
    explicit PlotRendererImgui(Context *context);
    ~PlotRendererImgui() = default;

    bool onPreRender() override;
    void onPostRender() override;
    void popupRender() override;
    virtual void onRender() = 0;
    virtual void onPopupRender() = 0;
protected:
    const ImVec4& getColor(); //imgui
    void setColor(ImVec4& color); //imgui
    ImVec4 _color{1, 1, 1, 1};

};


#endif //BROKERAPP_PLOTRENDERERIMGUI_H
