//
// Created by Luiz Veloso on 19/03/22.
//

#ifndef BROKERAPP_STOCKSEARCH_H
#define BROKERAPP_STOCKSEARCH_H

#ifndef IMGUI_CDECL
#ifdef _MSC_VER
#define IMGUI_CDECL __cdecl
#else
#define IMGUI_CDECL
#endif
#endif

#include "Widget.h"
#include <vector>
#include <map>

enum SymbolInfoColumnID
{
    SymbolInfoColumnID_Fav,
    SymbolInfoColumnID_Name,
    SymbolInfoColumnID_LastPrice,
    SymbolInfoColumnID_Delta,
};

struct SymbolRow {

    std::string name{"BTCUSDT"};
    std::string code{"BTCUSDT"};
    float lastPrice{10.0f};
    bool lastPriceSignal{true};
    float lastDayDelta{0.254f};

    static const ImGuiTableSortSpecs* s_current_sort_specs;


    // Compare function to be used by qsort()
    static int CompareWithSortSpecs(const void* lhs, const void* rhs)
    {
        const auto* a = (const SymbolRow*)lhs;
        const auto* b = (const SymbolRow*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
        {
            // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
            // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
            const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            switch (sort_spec->ColumnUserID)
            {
                case SymbolInfoColumnID_Name:  delta = (strcmp(a->name.c_str(), b->name.c_str())); break;
                case SymbolInfoColumnID_Delta: delta = (a->lastDayDelta - b->lastDayDelta); break;
                default: IM_ASSERT(0); break;
            }
            if (delta > 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
            if (delta < 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
        }

        // qsort() is instable so always return a way to differenciate items.
        // Your own compare function may want to avoid fallback on implicit sort specs e.g. a Name compare if it wasn't already part of the sort specs.
        return (strcmp(a->name.c_str(), b->name.c_str()));
    };
};



class StockSearch : public Widget {
public:
    StockSearch(Context* context);



    void updateVisible(float dt) override;
    void onPushStyleVar() override;

private:
    std::vector<std::shared_ptr<SymbolRow>> _symbols;
    void buildHeader();
    void buildFilter();
    void buildStockSearch();
    std::string _selectedTab = "Favs";
    bool populateFilteredSymbols = false;
    bool setupFirstTab = false;

    ImGuiTextFilter filter;
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
    std::vector<std::shared_ptr<SymbolRow>> filtered_symbols;

    void buildRow(SymbolRow info);

    void setFavoriteColumn(SymbolRow info);

    void setupTestSymbols();

    void buildTabBar();

    void applyTabFilter(std::string tabFilter);

};


#endif //BROKERAPP_STOCKSEARCH_H
