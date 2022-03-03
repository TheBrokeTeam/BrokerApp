//
// Created by Luiz Veloso on 27/02/22.
//

#ifndef BROKERAPP_DATASERIESRENDERERIMGUI_H
#define BROKERAPP_DATASERIESRENDERERIMGUI_H


#include "DataSeriesRenderer.h"
#include "IndicatorTickable.h"
#include <implot.h>
#include <implot_internal.h>

class DataSeriesRendererImgui: public DataSeriesRenderer {
public:
    explicit DataSeriesRendererImgui(Context *context);
    ~DataSeriesRendererImgui() = default;

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


#endif //BROKERAPP_DATASERIESRENDERERIMGUI_H
