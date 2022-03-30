//
// Created by Luiz Veloso on 19/03/22.
//

#ifndef BROKERAPP_STOCKSEARCH_H
#define BROKERAPP_STOCKSEARCH_H


#include "Widget.h"
#include <vector>

class StockSearch : public Widget {
public:
    StockSearch(Context* context);

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

private:
    // std::vector<std::shared_ptr<StockInfo>> _stocks;
    void buildHeader();
    static void cell();
    void buildFilter();
    void buildStockSearch();

    std::vector<std::string> symbols{"ETHBTC", "ETHBRL", "ETHUSDT", "BTCBRL", "BTCUSDT", "BTCBUSD"};
    bool favorites[6] = {false, true, false, true, false, true};
    std::vector<std::string> filtered_symbols;

    void buildRow(int row_number);

    void setFavoriteColumn(int row_number);
};



#endif //BROKERAPP_STOCKSEARCH_H
