//
// Created by Luiz Veloso on 31/12/21.
//

#ifndef BROKERAPP_STOCKLIST_H
#define BROKERAPP_STOCKLIST_H

#include "Widget.h"

class StockList : public Widget {
public:
    StockList(Editor* editor);

    struct StockInfo {
        std::string name{"Name"};
        std::string code{"NM.SA"};
        float price{10.0f};
        float lastPriceDelta{-0.01f};
        float volume{400};
        float relativeChange{0.05};
        float absoluteChange{0.35};
    };

    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void cell(StockInfo info);

private:
   // std::vector<std::shared_ptr<StockInfo>> _stocks;

};


#endif //BROKERAPP_STOCKLIST_H
