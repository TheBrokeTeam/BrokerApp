//
// Created by Luiz Veloso on 04/03/22.
//

#include "MainChartRenderer.h"
#include "MainSubplotRenderer.h"
#include "VolumeSubplotRenderer.h"

MainChartRenderer::MainChartRenderer(Ticker *ticker): ChartRenderer(ticker) {
    setName("MainChart");
    addPlotToChart(createMainSubplot());
    addPlotToChart(createVolumeSubplot());
}

std::shared_ptr<SubplotRenderer> MainChartRenderer::createMainSubplot() {
    std::shared_ptr<MainSubplotRenderer> subplotRenderer = std::make_unique<MainSubplotRenderer>(_ticker);
    return subplotRenderer;
}

std::shared_ptr<SubplotRenderer> MainChartRenderer::createVolumeSubplot() {
    std::shared_ptr<VolumeSubplotRenderer> subplotRenderer = std::make_unique<VolumeSubplotRenderer>(_ticker);
    return subplotRenderer;
}
