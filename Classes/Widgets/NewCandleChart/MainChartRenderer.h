//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_MAINCHARTRENDERER_H
#define BROKERAPP_MAINCHARTRENDERER_H

#include "ChartRenderer.h"

class MainChartRenderer: public ChartRenderer {
public:
    MainChartRenderer(Ticker* ticker);

    std::shared_ptr<SubplotRenderer> createMainSubplot();

    std::shared_ptr<SubplotRenderer> createVolumeSubplot();
};


#endif //BROKERAPP_MAINCHARTRENDERER_H
