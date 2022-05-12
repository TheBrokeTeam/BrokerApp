//
// Created by Luiz Veloso on 11/04/22.
//

#include "OrderLog.h"
#include <iomanip>
#include "../Contexts/Context.h"
#include "../Editor.h"

const ImGuiTableSortSpecs* OrderRow::s_current_sort_specs = NULL;

OrderLog::OrderLog(Context *context) : Widget(context)
{
    _title                  = "Order Log";
    _is_window              = true;
    setupTestOrder();
    setupTestOrder();
    setupTestOrder();
}


void OrderLog::setupTestOrder() {
    OrderRow row = OrderRow();
    row.date = std::time(0);

    row.orderID = "0103939413";
    row.amount = 100.0;
    row.pair = "ETHBTC";
    row.average = 50.0;

    row.executed = 0.01;
    row.fee = 0.010;
    row.filled = 0.10;
    row.side = TradeSideType::Buy;
    row.status = OrderStatusType::PartiallyFilled;
    row.stopLoss = 10;
    row.takeProfit = 200;
    row.total = 100;
    row.type = OrderType::Limit;
    row.price = 5000.1;
    row.triggerConditions = ">=200 & <= 10";
    getContext()->;

}

std::string OrderLog::getTabName(OrderLogTabBarType tab) {
    switch (tab) {
        case OpenOrders: return "Open Orders";
        case OrderHistory: return "Order History";
        case TradeHistory: return "Trade History";
        case Funds: return "Funds";
    }
}

std::string OrderLog::getSideName(TradeSideType side) {
    switch (side) {
        case TradeSideType::Buy:
            return "Buy";
        case TradeSideType::Sell:
            return "Sell";
    }
}

std::string OrderLog::getStatusTypeName(OrderStatusType statusType) {
    switch (statusType) {
        case Filled:
            return "Filled";
        case PartiallyFilled:
            return "PartiallyFilled";
        case Expired:
            return "Expired";
        case Cancelled:
            return "Cancelled";
    }
}

std::string OrderLog::getOrderTypeName(OrderType type) {
   switch (type) {
       case Limit: return "Limit";
       case Market: return "Market";
       case LimitStop: return "Limit-Stop";
       case OCO: return "OCO";
   }
}


void OrderLog::buildTabBar() {
    OrderLogTabBarType tabnames[] = {OrderLogTabBarType::OpenOrders,
                                     OrderLogTabBarType::OrderHistory,
                                     OrderLogTabBarType::TradeHistory,
                                     OrderLogTabBarType::Funds};

    for (auto &name: tabnames) {
        if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem(OrderLog::getTabName(name).c_str())) {
                if (_selectedTab != name || !setupFirstTab) {
                    filtered_symbols.clear();
                    for (auto & symbol : _orders) {
                        if (filter.PassFilter(symbol.orderID.c_str()))
                            filtered_symbols.push_back(symbol);
                    }
                    //applyTabFilter(name);
                    _selectedTab = name;
                    setupFirstTab = true;
                }

                buildOrderLog();
                ImGui::EndTabItem();

            }

            ImGui::EndTabBar();

        }
    }
}

void OrderLog::applyTabFilter(std::string tabFilter) {

//    if (tabFilter == "All") {
//        return;
//    } else if (tabFilter == "Favs") {
//        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
//            return !i.favorited;
//        }), filtered_symbols.end());
//
//    } else {
//        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
//            return (i.name).find(tabFilter) == std::string::npos;
//        }), filtered_symbols.end());
//
//    }
}

void OrderLog::updateVisible(float dt)
{
    buildHeader();
    buildFilter();
    buildTabBar();
}


void OrderLog::buildHeader() {//change background of window
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    //change color text
    PushStyleColor(ImGuiCol_Text, Editor::broker_white);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg, Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive, Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered, Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg, Editor::broker_white);

    ImGui::TextColored(Editor::broker_white,"Order Log");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button, Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive, Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered, Editor::broker_clear);

    //adding the close button
    auto info = getContext()->getEditor()->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*3);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        SetVisible(false);
    }

    ImGui::Separator();
    ImGui::Spacing();
}

void OrderLog::buildFilter() {

    // Helper class to easy setup a text filter.
    // You may want to implement a more feature-full filtering scheme in your own application.

    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(style.FramePadding.x, (float) (int) (style.FramePadding.y * 1.0f)));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);

    filter.Draw("##SearchFilter", ImGui::GetWindowWidth()-30);

    if (ImGui::IsItemEdited() || !populateFilteredSymbols) {
        filtered_symbols.clear();
        for (auto & symbol : _orders) {
            if (filter.PassFilter(symbol.orderID.c_str()))
                filtered_symbols.push_back(symbol);
        }
        populateFilteredSymbols = true;
        //applyTabFilter(_selectedTab);
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(1);
    ImGui::Spacing();
    ImGui::Separator();


}


void OrderLog::buildOrderLog() {


    static ImGuiTableFlags flags =   ImGuiTableFlags_ScrollY | ImGuiTableFlags_SortMulti | ImGuiTableFlags_Sortable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;

    switch (_selectedTab) {
        case OpenOrders:
            if (ImGui::BeginTable("Table_OpenOrders", 11, flags)) {
                // Display headers so we can inspect their interaction with borders.
                // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
                ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_OrderID);
                ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Date);
                ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 185, OrderColumnID_Pair);
                ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Type);
                ImGui::TableSetupColumn("Side", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Side);
                ImGui::TableSetupColumn("Price", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Price);
                //ImGui::TableSetupColumn("Executed", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Executed);
                //ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Status);
                ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Amount);
                ImGui::TableSetupColumn("Filled", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Filled);
                ImGui::TableSetupColumn("Total", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Total);
                ImGui::TableSetupColumn("Trigger Conditions", ImGuiTableColumnFlags_WidthFixed, 185, OrderColumnID_TriggerConditions);
                //ImGui::TableSetupColumn("Average", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Average);
                ImGui::TableSetupColumn("Cancel", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort, 80, OrderColumnID_Cancel);

                ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
                ImGui::TableHeadersRow();
                ImGui::PopStyleColor();

                // Sort our data if sort specs have been changed!
                if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
                    if (sorts_specs->SpecsDirty) {
                        OrderRow::s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
                        if (filtered_symbols.size() > 1) {
                            qsort(&filtered_symbols[0], (size_t)filtered_symbols.size(), sizeof(filtered_symbols[0]), OrderRow::CompareWithSortSpecs);

                        }

                        OrderRow::s_current_sort_specs = NULL;
                        sorts_specs->SpecsDirty = false;

                    }

                for (auto& filtered: filtered_symbols) {
                    buildRow(filtered);
                }

                ImGui::EndTable();
            }

            break;

        case OrderHistory:
            if (ImGui::BeginTable("Table_OrderHistory", 12, flags)) {
                // Display headers so we can inspect their interaction with borders.
                // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
                ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_OrderID);
                ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Date);
                ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 185, OrderColumnID_Pair);
                ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Type);
                ImGui::TableSetupColumn("Side", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Side);
                ImGui::TableSetupColumn("Average", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Average);

                ImGui::TableSetupColumn("Price", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Price);
                ImGui::TableSetupColumn("Executed", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Executed);
                ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Amount);
                //ImGui::TableSetupColumn("Filled", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Filled);
                ImGui::TableSetupColumn("Total", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Total);
                ImGui::TableSetupColumn("Trigger Conditions", ImGuiTableColumnFlags_WidthFixed, 185, OrderColumnID_TriggerConditions);
                ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Status);
                //ImGui::TableSetupColumn("Cancel", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Cancel);

                ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
                ImGui::TableHeadersRow();
                ImGui::PopStyleColor();


                // Sort our data if sort specs have been changed!
                if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
                    if (sorts_specs->SpecsDirty) {
                        OrderRow::s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
                        if (filtered_symbols.size() > 1) {
                            qsort(&filtered_symbols[0], (size_t)filtered_symbols.size(), sizeof(filtered_symbols[0]), OrderRow::CompareWithSortSpecs);

                        }

                        OrderRow::s_current_sort_specs = NULL;
                        sorts_specs->SpecsDirty = false;

                    }

                for (auto& filtered: filtered_symbols) {
                    buildRow(filtered);
                }

                ImGui::EndTable();
            }
            break;

        case TradeHistory:
            if (ImGui::BeginTable("Table_TradeHistory", 8, flags)) {
                // Display headers so we can inspect their interaction with borders.
                // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
                ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_OrderID);
                ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Date);
                ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 185, OrderColumnID_Pair);
                //ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Type);
                ImGui::TableSetupColumn("Side", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Side);
                ImGui::TableSetupColumn("Price", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Price);
                ImGui::TableSetupColumn("Executed", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Executed);
//                ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Status);
//                ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Amount);
//                ImGui::TableSetupColumn("Filled", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Filled);
                ImGui::TableSetupColumn("Fee", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Fee);
                ImGui::TableSetupColumn("Total", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Total);
//                ImGui::TableSetupColumn("Trigger Conditions", ImGuiTableColumnFlags_WidthFixed, 185, OrderColumnID_TriggerConditions);
//                ImGui::TableSetupColumn("Average", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Average);
//                ImGui::TableSetupColumn("Cancel", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Cancel);

                ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
                ImGui::TableHeadersRow();
                ImGui::PopStyleColor();


                // Sort our data if sort specs have been changed!
                if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
                    if (sorts_specs->SpecsDirty) {
                        OrderRow::s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
                        if (filtered_symbols.size() > 1) {
                            qsort(&filtered_symbols[0], (size_t)filtered_symbols.size(), sizeof(filtered_symbols[0]), OrderRow::CompareWithSortSpecs);

                        }

                        OrderRow::s_current_sort_specs = NULL;
                        sorts_specs->SpecsDirty = false;

                    }

                for (auto& filtered: filtered_symbols) {
                    buildRow(filtered);
                }

                ImGui::EndTable();
            }
            break;

        case Funds:
            if (ImGui::BeginTable("Table_Funds", 14, flags)) {
                // Display headers so we can inspect their interaction with borders.
                // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
                ImGui::TableSetupColumn("ID", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_OrderID);
                ImGui::TableSetupColumn("Date", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Date);
                ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 185, OrderColumnID_Pair);
                ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Type);
                ImGui::TableSetupColumn("Side", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 75, OrderColumnID_Side);
                ImGui::TableSetupColumn("Price", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Price);
                ImGui::TableSetupColumn("Executed", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Executed);
                ImGui::TableSetupColumn("Status", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Status);
                ImGui::TableSetupColumn("Amount", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Amount);
                ImGui::TableSetupColumn("Filled", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Filled);
                ImGui::TableSetupColumn("Total", ImGuiTableColumnFlags_WidthFixed, 75, OrderColumnID_Total);
                ImGui::TableSetupColumn("Trigger Conditions", ImGuiTableColumnFlags_WidthFixed, 185, OrderColumnID_TriggerConditions);
                ImGui::TableSetupColumn("Average", ImGuiTableColumnFlags_WidthFixed, 80, OrderColumnID_Average);
                ImGui::TableSetupColumn("Cancel", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort, 80, OrderColumnID_Cancel);

                ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
                ImGui::TableHeadersRow();
                ImGui::PopStyleColor();


                // Sort our data if sort specs have been changed!
                if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
                    if (sorts_specs->SpecsDirty) {
                        OrderRow::s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
                        if (filtered_symbols.size() > 1) {
                            qsort(&filtered_symbols[0], (size_t)filtered_symbols.size(), sizeof(filtered_symbols[0]), OrderRow::CompareWithSortSpecs);

                        }

                        OrderRow::s_current_sort_specs = NULL;
                        sorts_specs->SpecsDirty = false;

                    }

                for (auto& filtered: filtered_symbols) {
                    buildRow(filtered);
                }

                ImGui::EndTable();
            }
            break;
    }
}

void OrderLog::buildRow(OrderRow &info) {
    enum ContentsType {
        CT_Text, CT_FillButton
    };
    static int contents_type = CT_Text;

    ImGui::TableNextRow();

    int columnCount;

    switch (_selectedTab) {
        case OpenOrders: columnCount = 11 ; break;
        case OrderHistory: columnCount = 12; break;
        case TradeHistory: columnCount = 8; break;
        case Funds: columnCount = 14; break;
    }

    for (int column = 0; column < columnCount; column++) {
        ImGui::TableSetColumnIndex(column);

        if (strcmp(ImGui::TableGetColumnName(column),"ID") == 0) {
            ImGui::PushID(("##" + getTabName(_selectedTab) + "_selectable_row_" + info.orderID).c_str());
            if (ImGui::Selectable("##selectable_row", false,
                                  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap,
                                  ImVec2(0, 0))) {
                printf("touched %s\n", info.orderID.c_str());
                _orderID = info.orderID;
                changeStream();
            }
            ImGui::PopID();
            ImGui::SameLine();
            ImGui::TextColored(Editor::broker_white, "%s", info.orderID.c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Date") == 0) {
            ///default way... not custom date format
            //std::string h = std::string (ctime (&info.date));

            ///with custom date format
            struct tm *timeinfo;
            char buffer [80];

            timeinfo = localtime(&info.date);
            strftime (buffer, 80,"%Y-%m-%d-%H-%M-%S",timeinfo);

            ImGui::TextColored(Editor::broker_white, "%s", buffer);


        } else if (strcmp(ImGui::TableGetColumnName(column), "Pair") == 0) {
            ImGui::TextColored(Editor::broker_white, "%s", info.pair.c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Type") == 0) {
            ImGui::TextColored(Editor::broker_white, "%s", (getOrderTypeName(info.type)).c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Side") == 0) {
            ImGui::TextColored(Editor::broker_white, "%s", (getSideName(info.side)).c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Price") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.price);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Executed") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.executed);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Status") == 0) {
            ImGui::TextColored(Editor::broker_white, "%s", (getStatusTypeName(info.status)).c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Amount") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.amount);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Filled") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.filled);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Total") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.total);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Fee") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.fee);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Trigger Conditions") == 0) {
            ImGui::TextColored(Editor::broker_white, "%s", info.triggerConditions.c_str());

        } else if (strcmp(ImGui::TableGetColumnName(column), "Average") == 0) {
            ImGui::TextColored(Editor::broker_white, "%.2f", info.average);

        } else if (strcmp(ImGui::TableGetColumnName(column), "Cancel") == 0) {
            setCancelColumn(info);

        }
    }
}



void OrderLog::setCancelColumn(OrderRow &order) {

    auto info = getContext()->getEditor()->getTexture(Editor::Icons::trash);

    ImGui::PushID(("cancel_" + order.orderID).c_str());

    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*3);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width*0.7,info.my_image_height*0.7))){
       //deleta a ordem
       //remove/atualiza a ordem
        removeItem(order);
    }
    ImGui::PopID();

}

void OrderLog::removeItem(OrderRow &order) {

    ImVector<OrderRow>::iterator it = std::find_if(_orders.begin(), _orders.end(), [&](const OrderRow & o) {
        return o.orderID == order.orderID;
    });

    int index = std::distance(_orders.begin(), it);

    if (it != _orders.end())
    {
        _orders.erase(_orders.begin() + index); // not working yet
    }

    printf("remove");

}

void OrderLog::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}


void OrderLog::changeStream() {
    getContext()->closeSymbolStream(Symbol(_oldSymbolName,"1m",0,0));
    _symbol =   Symbol(_orderID, "1m", 0, 0);
    getContext()->openSymbolStream(_symbol);
    _oldSymbolName = _orderID;
}

