//
// Created by Luiz Veloso on 02/03/22.
//

#ifndef BROKERAPP_CHARTRENDERER_H
#define BROKERAPP_CHARTRENDERER_H

#include <vector>
#include "DataSeriesRenderer.h"


class ChartRenderer {
    std::vector<DataSeriesRenderer> subplots;
    void render();
    void updateVisible(float dt);
};


#endif //BROKERAPP_CHARTRENDERER_H
