//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_VOLUMESUBPLOTRENDERER_H
#define BROKERAPP_VOLUMESUBPLOTRENDERER_H

#include "SubplotRenderer.h"


//#define dataHist (*_ticker->getBarHistory())

class VolumeSubplotRenderer: public SubplotRenderer {

public:
    explicit VolumeSubplotRenderer(Ticker *ticker);

private:

    void onPreRender() override;
    void onSetupPlot() override;
    void onPostRender() override;

    void addVolumeItem();
};


#endif //BROKERAPP_VOLUMESUBPLOTRENDERER_H
