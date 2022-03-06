//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_VOLUMERENDERER_H
#define BROKERAPP_VOLUMERENDERER_H


#include "VolumeData.h"
#include "DataSeriesRendererImgui.h"
#include "../Tickers/Ticker.h"
#include "../Contexts/Context.h"
class VolumeRenderer : public DataSeriesRendererImgui {
public:
    VolumeRenderer(Context *context, VolumeData *data);

    ~VolumeRenderer();

    void onRender() override;
    void onPopupRender() override;

protected:
    float _lineWidth = 2.0f;
    VolumeData* _data{};
};


#endif //BROKERAPP_VOLUMERENDERER_H
