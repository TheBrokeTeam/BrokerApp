//
// Created by Luiz Veloso on 02/03/22.
//

#ifndef BROKERAPP_MAINSUBPLOTRENDERER_H
#define BROKERAPP_MAINSUBPLOTRENDERER_H

#include "SubplotRenderer.h"
#include "OHLCData.h"

//#define dataHist (*_ticker->getBarHistory())

class MainSubplotRenderer: public SubplotRenderer {

public:
    explicit MainSubplotRenderer(Ticker *ticker);
    void addOHLCItem(OHLCData* ohlcData);

private:

    void onPreRender() override;
    void onSetupPlot() override;
    void onPostRender() override;

};


#endif //BROKERAPP_MAINSUBPLOTRENDERER_H
