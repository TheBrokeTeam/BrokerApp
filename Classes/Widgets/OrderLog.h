//
// Created by Luiz Veloso on 11/04/22.
//

#ifndef BROKERAPP_ORDERLOG_H
#define BROKERAPP_ORDERLOG_H


#include "Widget.h"
#include <vector>
#include <map>
#include "../Data/Symbol.h"


enum OrderInfoColumnID
{
    OrderColumnID_Date,
    OrderColumnID_Pair,
    OrderColumnID_Type,
    OrderColumnID_Side,
    OrderColumnID_Executed,
    OrderColumnID_Status,
    OrderColumnID_OrderID,
    OrderColumnID_Price,
    OrderColumnID_Amount,
    OrderColumnID_Filled,
    OrderColumnID_Total,
    OrderColumnID_TriggerConditions,
    OrderColumnID_Average,
    OrderColumnID_Cancel,
    OrderColumnID_Fee
};

enum OrderLogTabBarType {
    OpenOrders,
    OrderHistory,
    TradeHistory,
    Funds
};

struct OrderRow {

    std::string orderID;
    time_t date;
    std::string pair;

    TradeSideType side;
    OrderType type;
    OrderStatusType status;

    float executed;

    float price;
    float fee;
    float amount;
    float filled;
    float total;
    float stopLoss;
    float takeProfit;
    float average;
    std::string triggerConditions;

    static const ImGuiTableSortSpecs* s_current_sort_specs;


    // Compare function to be used by qsort()
    static int CompareWithSortSpecs(const void* lhs, const void* rhs)
    {
        const auto* a = (const OrderRow*)lhs;
        const auto* b = (const OrderRow*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
        {
            // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
            // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
            const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            switch (sort_spec->ColumnUserID) {
                case OrderColumnID_OrderID: delta = strcmp(a->orderID.c_str(),b->orderID.c_str()) ; break;
                case OrderColumnID_Date: delta = (a->date - b->date) ; break;
                case OrderColumnID_Pair: delta = strcmp(a->pair.c_str(),b->pair.c_str()) ; break;

                case OrderColumnID_Type: delta = (int(a->type) - int(b->type)) ; break;
                case OrderColumnID_Side: delta = (int(a->side) - int(b->side)) ; break;

                case OrderColumnID_Executed: delta = (int(a->executed*100) - int(b->executed*100)) ; break;
                case OrderColumnID_Status: delta = (int(a->status) - int(b->status)) ; break;

                case OrderColumnID_Price: delta = (int(a->price*100) - int(b->price*100)) ; break;
                case OrderColumnID_Fee: delta = (int(a->fee*100) - int(b->fee*100)) ; break;
                case OrderColumnID_Amount: delta = (int(a->amount*100) - int(b->amount*100)) ; break;
                case OrderColumnID_Filled: delta = (int(a->filled*100) - int(b->filled*100)) ; break;
                case OrderColumnID_Total: delta = (int(a->total*100) - int(b->total*100)) ; break;
                case OrderColumnID_TriggerConditions: delta = strcmp(a->triggerConditions.c_str(), b->triggerConditions.c_str()) ; break;
                case OrderColumnID_Average: delta = (int(a->average) - int(b->average)) ; break;
               // case OrderColumnID_Cancel: delta = strcmp(a->orderID.c_str(),b->orderID.c_str())          ; break;

                default: IM_ASSERT(0); break;
            }
            if (delta > 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
            if (delta < 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
        }

        // qsort() is instable so always return a way to differenciate items.
        // Your own compare function may want to avoid fallback on implicit sort specs e.g. a Name compare if it wasn't already part of the sort specs.
        return strcmp(a->orderID.c_str(),b->orderID.c_str());
    };
};



class OrderLog : public Widget {
public:
    OrderLog(Context* context);

    void updateVisible(float dt) override;
    void onPushStyleVar() override;

private:
    //ImVector<OrderRow> _orders;

    void buildHeader();
    void buildFilter();
    void buildOrderLog();
    bool populateFilteredSymbols = false;
    bool setupFirstTab = false;

    ImGuiTextFilter filter;
    ImVector<OrderRow> filtered_symbols;

    void buildRow(OrderRow &info);

    void setCancelColumn(OrderRow &info);

    void buildTabBar();

    void setupTestOrder();

    void applyTabFilter(std::string tabFilter);

    void setupTestSymbols();
    void changeStream();
    Symbol _symbol{"ETHUSDT","1m",0,0};
    std::string _orderID{"ETHUSDT"};
    std::string _oldSymbolName;

    OrderLogTabBarType _selectedTab = OrderLogTabBarType::OpenOrders;

    std::string getTabName(OrderLogTabBarType tabname);


    std::string getSideName(TradeSideType side);
    std::string getOrderTypeName(OrderType type);
    std::string getStatusTypeName(OrderStatusType statusType);

    void removeItem(OrderRow &order);
};



#endif //BROKERAPP_ORDERLOG_H
