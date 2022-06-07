//
// Created by Luiz Veloso on 19/03/22.
//

#include "StockSearch.h"
#include <iomanip>
#include "../Contexts/Context.h"
#include "../Editor.h"

const ImGuiTableSortSpecs* SymbolRow::s_current_sort_specs = NULL;

StockSearch::StockSearch(Context *context) : Widget(context)
{
    _title                  = "Stock Search";
    _is_window              = true;
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();

}


void StockSearch::setupTestSymbols() {
    SymbolRow row = SymbolRow();
    row.code = "BTCUSDT";
    row.lastPriceSignal = false;
    row.lastDayDelta = 0.0342;
    row.lastPrice = 43938.230;
    row.name = "BTCUSDT";
    row.favorited = true;
    _symbols.push_back(row);

    row.code = "BTCBUSD";
    row.lastPriceSignal = true;
    row.lastDayDelta = -0.0351;
    row.lastPrice = 43912.27;
    row.name = "BTCBUSD";
    row.favorited = false;
    _symbols.push_back(row);

    row. code = "ETHBTC";
    row. lastPriceSignal = true;
    row.lastDayDelta = 0.0167;
    row.lastPrice = 0.073638;
    row.name = "ETHBTC";
    row.favorited = false;
    _symbols.push_back(row);

    row. code = "ETHBRL";
    row. lastPriceSignal = true;
    row.lastDayDelta = -0.0385;
    row.lastPrice = 15353.98;
    row.name = "ETHBRL";
    row.favorited = true;
    _symbols.push_back(row);

    row. code = "BTCBRL";
    row. lastPriceSignal = false;
    row.lastDayDelta = -0.0214;
    row.lastPrice = 208731;
    row.name = "BTCBRL";
    row.favorited = true;
    _symbols.push_back(row);

    row.code = "ETHUSDT";
    row.lastPriceSignal = true;
    row.lastDayDelta = 0.0527;
    row.lastPrice = 3227.89;
    row.name = "ETHUSDT";
    row.favorited = false;
    _symbols.push_back(row);
}


void StockSearch::buildTabBar() {
    std::string tabnames[] = {"Favs", "All", "USDT", "BTC", "BRL", "ETH"};

    for (auto &name: tabnames) {
        if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem(name.c_str())) {
                if (_selectedTab != name || !setupFirstTab) {
                    filtered_symbols.clear();
                    for (auto & symbol : _symbols) {
                        if (filter.PassFilter(symbol.name.c_str()))
                            filtered_symbols.push_back(symbol);
                    }
                    applyTabFilter(name);
                    _selectedTab = name;
                    setupFirstTab = true;
                }

                buildStockSearch();
                ImGui::EndTabItem();

            }

            ImGui::EndTabBar();

        }
    }
}

void StockSearch::applyTabFilter(std::string tabFilter) {

    if (tabFilter == "All") {
        return;
    } else if (tabFilter == "Favs") {
        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
            return !i.favorited;
        }), filtered_symbols.end());

    } else {
        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
            return (i.name).find(tabFilter) == std::string::npos;
        }), filtered_symbols.end());

    }
}

void StockSearch::updateVisible(float dt)
{
    buildHeader();
    buildFilter();
    buildTabBar();
}


void StockSearch::buildHeader() {//change background of window
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

    ImGui::TextColored(Editor::broker_white,"Stock Search");
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

void StockSearch::buildFilter() {

        // Helper class to easy setup a text filter.
        // You may want to implement a more feature-full filtering scheme in your own application.

    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(style.FramePadding.x, (float) (int) (style.FramePadding.y * 1.0f)));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);

    filter.Draw("##SearchFilter", ImGui::GetWindowWidth()-30);

    if (ImGui::IsItemEdited() || !populateFilteredSymbols) {
        filtered_symbols.clear();
        for (auto & symbol : _symbols) {
            if (filter.PassFilter(symbol.name.c_str()))
                filtered_symbols.push_back(symbol);
        }
        populateFilteredSymbols = true;
        applyTabFilter(_selectedTab);
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(1);
    ImGui::Spacing();
    ImGui::Separator();


}


void StockSearch::buildStockSearch() {


    static ImGuiTableFlags flags =   ImGuiTableFlags_ScrollY | ImGuiTableFlags_SortMulti | ImGuiTableFlags_Sortable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;

    if (ImGui::BeginTable("Table1", 4, flags)) {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        ImGui::TableSetupColumn("Fav", ImGuiTableColumnFlags_WidthFixed, 40, SymbolInfoColumnID_Fav);
        ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 185, SymbolInfoColumnID_Name);
        ImGui::TableSetupColumn("Last", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 75, SymbolInfoColumnID_LastPrice);
        ImGui::TableSetupColumn("24h", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 60, SymbolInfoColumnID_Delta);

        ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
        ImGui::TableHeadersRow();
        ImGui::PopStyleColor();


        // Sort our data if sort specs have been changed!
        if (ImGuiTableSortSpecs* sorts_specs = ImGui::TableGetSortSpecs())
            if (sorts_specs->SpecsDirty) {
                SymbolRow::s_current_sort_specs = sorts_specs; // Store in variable accessible by the sort function.
                if (filtered_symbols.size() > 1) {
                    qsort(&filtered_symbols[0], (size_t)filtered_symbols.size(), sizeof(filtered_symbols[0]), SymbolRow::CompareWithSortSpecs);

                }

                SymbolRow::s_current_sort_specs = NULL;
                sorts_specs->SpecsDirty = false;

            }

        for (auto& filtered: filtered_symbols) {
            buildRow(filtered);

        }

        ImGui::EndTable();
    }
}

void StockSearch::buildRow(SymbolRow &info) {
    enum ContentsType {
        CT_Text, CT_FillButton
    };
    static int contents_type = CT_Text;

    ImGui::TableNextRow();

    for (int column = 0; column < 4; column++) {
        ImGui::TableSetColumnIndex(column);

        if (column == 0) {
            ImGui::PushID(("##selectable_row" + info.name).c_str());
            if (ImGui::Selectable("##selectable_row", false,
                                  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap,
                                  ImVec2(0, 0))) {
                printf("touched %s\n", info.name.c_str());
                _symbolName = info.code;
                changeStream();
            }
            ImGui::PopID();
            ImGui::SameLine();
            setFavoriteColumn(info);

        } else if (column == 1) {
            ImGui::TextColored(Editor::broker_white, "%s", info.code.c_str());

        } else if (column == 2) {
            ImVec4 lastPriceColor = info.lastPriceSignal ? Editor::broker_green : Editor::broker_red;
            ImGui::TextColored(lastPriceColor, "%.2f", info.lastPrice);

        } else if (column == 3) {
            ImVec4 lastDayDeltaColor = info.lastDayDelta>0 ? Editor::broker_green : Editor::broker_red;
            ImGui::TextColored(lastDayDeltaColor, "%+.2f%%", info.lastDayDelta * 100);

        }

    }

}



void StockSearch::setFavoriteColumn(SymbolRow &info) {

    ImGui::PushID(("favorite_checkbox_" + info.name).c_str());
   // ImGui::Checkbox("##Checkbox1", &favorites[row_number]);

    Editor::Icons state = info.favorited ? Editor::Icons::fav_selected : Editor::Icons::fav_unselected;
    auto texture = getContext()->getEditor()->getTexture(state);

    if(ImGui::ImageButton((void*)(intptr_t)texture.my_image_texture, ImVec2(15, 15))){
        ImVector<SymbolRow>::iterator it = std::find_if(_symbols.begin(), _symbols.end(), [&](const SymbolRow & o) {
            return o.code == info.code;
        });

        it->favorited = info.favorited ? false : true;
        info.favorited = info.favorited ? false : true;
    }
    ImGui::PopID();

}

void StockSearch::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}



void StockSearch::changeStream() {
    getContext()->closeSymbolStream(Symbol(_oldSymbolName,"1m",0,0));
    _symbol =   Symbol(_symbolName,"1m",0,0);
    getContext()->openSymbolStream(_symbol);
    _oldSymbolName = _symbolName;
}