//
// Created by Luiz Veloso on 19/03/22.
//

#ifndef BROKERAPP_STOCKSEARCH_H
#define BROKERAPP_STOCKSEARCH_H


#include "Widget.h"
#include <vector>
#include <map>

class StockSearch : public Widget {
public:
    StockSearch(Context* context);

    struct SymbolInfo {
        std::string name{"BTCUSDT"};
        std::string code{"BTCUSDT"};
        float lastPrice{10.0f};
        bool lastPriceSignal{true};
        float lastDayDelta{0.254f};
    };

    void updateVisible(float dt) override;
    void onPushStyleVar() override;

private:
    std::vector<std::shared_ptr<SymbolInfo>> _symbols;
    void buildHeader();
    static void cell();
    void buildFilter();
    void buildStockSearch();

    std::map<std::string, bool> _favorites = {
            {"ETHBTC", false},
            {"ETHBRL", false},
            {"ETHUSDT", true},
            {"BTCBRL", false},
            {"BTCUSDT", true},
            {"BTCBUSD", false}
    };

    //std::vector<std::string> symbols{"ETHBTC", "ETHBRL", "ETHUSDT", "BTCBRL", "BTCUSDT", "BTCBUSD"};
    //bool favorites[6] = {false, true, false, true, false, true}; //lv: map
    std::vector<std::shared_ptr<SymbolInfo>> filtered_symbols;

    void buildRow(SymbolInfo info);

    void setFavoriteColumn(SymbolInfo info);

    void setupTestSymbols();

    void buildTabBar();

    void applyTabFilter(std::string tabFilter);
};



#endif //BROKERAPP_STOCKSEARCH_H
