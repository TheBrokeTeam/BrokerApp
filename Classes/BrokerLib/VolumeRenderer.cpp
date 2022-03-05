//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeRenderer.h"

#include "implot.h"

VolumeRenderer::VolumeRenderer(Context *context, VolumeData *data): DataSeriesRendererImgui(context) {
    _data = data;
    setPlotName("Volume");
}

void VolumeRenderer::onRender() {}

void VolumeRenderer::onPopupRender() {}

VolumeRenderer::~VolumeRenderer() {}

