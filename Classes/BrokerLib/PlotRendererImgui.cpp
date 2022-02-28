//
// Created by Luiz Veloso on 27/02/22.
//

#include "PlotRendererImgui.h"
#include "implot.h"

PlotRendererImgui::PlotRendererImgui(Context *context): PlotRenderer(context) {}



bool PlotRendererImgui::onPreRender() {
    return ImPlot::BeginItem(_plotName.c_str());
}

void PlotRendererImgui::onPostRender() {
    ImPlot::EndItem();
}

const ImVec4 &PlotRendererImgui::getColor() {
    return _color;
}

void PlotRendererImgui::setColor(ImVec4 &color) {
    _color = color;
}

//void PlotRendererImgui::onRender() {
//
//}
//
//void PlotRendererImgui::onPopupRender() {
//
//}