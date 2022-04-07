//
// Created by Luiz Veloso on 19/03/22.
//

#include "StockSearch.h"
#include <iomanip>
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"

StockSearch::StockSearch(Context *context) : Widget(context)
{
    _title                  = "Stock Search";
    _is_window              = true;
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();
    setupTestSymbols();


}

void StockSearch::setupTestSymbols() {
    std::__1::shared_ptr<SymbolInfo> btcusdt = std::__1::make_shared<SymbolInfo>();
    btcusdt->code = "BTCUSDT";
    btcusdt->lastPriceSignal = false;
    btcusdt->lastDayDelta = 0.0342;
    btcusdt->lastPrice = 43938.230;
    btcusdt->name = "BTCUSDT";
    _symbols.push_back(btcusdt);

    std::__1::shared_ptr<SymbolInfo> btcbusd = std::__1::make_shared<SymbolInfo>();
    btcbusd->code = "BTCBUSD";
    btcbusd->lastPriceSignal = true;
    btcbusd->lastDayDelta = -0.0351;
    btcbusd->lastPrice = 43912.27;
    btcbusd->name = "BTCBUSD";
    _symbols.push_back(btcbusd);

    std::__1::shared_ptr<SymbolInfo> ethbtc = std::__1::make_shared<SymbolInfo>();
    ethbtc-> code = "ETHBTC";
    ethbtc-> lastPriceSignal = true;
    ethbtc->lastDayDelta = 0.0167;
    ethbtc->lastPrice = 0.073638;
    ethbtc->name = "ETHBTC";
    _symbols.push_back(ethbtc);

    std::__1::shared_ptr<SymbolInfo> ethbrl = std::__1::make_shared<SymbolInfo>();
    ethbrl-> code = "ETHBRL";
    ethbrl-> lastPriceSignal = true;
    ethbrl->lastDayDelta = -0.0385;
    ethbrl->lastPrice = 15353.98;
    ethbrl->name = "ETHBRL";
    _symbols.push_back(ethbrl);

    std::__1::shared_ptr<SymbolInfo> btcbrl = std::__1::make_shared<SymbolInfo>();
    btcbrl-> code = "BTCBRL";
    btcbrl-> lastPriceSignal = false;
    btcbrl->lastDayDelta = -0.0214;
    btcbrl->lastPrice = 208731;
    btcbrl->name = "BTCBRL";
    _symbols.push_back(btcbrl);

    std::__1::shared_ptr<SymbolInfo> ethusdt = std::__1::make_shared<SymbolInfo>();
    ethusdt->code = "ETHUSDT";
    ethusdt->lastPriceSignal = true;
    ethusdt->lastDayDelta = 0.0527;
    ethusdt->lastPrice = 3227.89;
    ethusdt->name = "ETHUSDT";
    _symbols.push_back(ethusdt);
}

void StockSearch::buildTabBar() {
    std::string tabnames[]{"Favs", "All", "USDT", "BTC", "BRL", "ETH"};

    for (auto &name: tabnames) {

        if (ImGui::BeginTabBar("MyTabBar", ImGuiTabBarFlags_None)) {
            if (ImGui::BeginTabItem(name.c_str())) {
                applyTabFilter(name);
                buildStockSearch();
                //ImGui::Text("This is the Avocado tab!\nblah blah blah blah blah");
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
    }
}

void StockSearch::applyTabFilter(std::string tabFilter) {
    //std::vector<std::shared_ptr<SymbolInfo>> tab_filtered_symbols = {nullptr};

    if (tabFilter == "All") {
        return;
    } else if (tabFilter == "Favs") {
        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
            return !_favorites[i->name];
        }), filtered_symbols.end());

    } else {
        filtered_symbols.erase(std::remove_if(filtered_symbols.begin(), filtered_symbols.end(), [&](auto& i) {
            return (i->name).find(tabFilter) == std::string::npos;
        }), filtered_symbols.end());

    }

    //filtered_symbols.clear();
    //filtered_symbols = tab_filtered_symbols;
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

    static ImGuiTextFilter filter;

    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(style.FramePadding.x, (float) (int) (style.FramePadding.y * 1.0f)));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);

    filter.Draw("##SearchFilter", ImGui::GetWindowWidth()-30);
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(1);
    ImGui::Spacing();
    ImGui::Separator();

   // const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };

    filtered_symbols.clear();

     for (auto & symbol : _symbols) {
         if (filter.PassFilter(symbol->name.c_str()))
             filtered_symbols.push_back(symbol);
     }


}


void StockSearch::buildStockSearch() {

    // Expose a few Borders related flags interactively

    static ImGuiTableFlags flags =  ImGuiTableFlags_Sortable | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg ;
    //static bool display_headers = false;


    ///PushStyleCompact()
    ImGuiStyle &style = ImGui::GetStyle();
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding,
                        ImVec2(style.FramePadding.x, (float) (int) (style.FramePadding.y * 0.60f)));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing,
                        ImVec2(style.ItemSpacing.x, (float) (int) (style.ItemSpacing.y * 0.60f)));

    // finish PushStyleCompact()
//
//    ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
//    ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &flags, ImGuiTableFlags_Borders);
//    ImGui::SameLine();
//    HelpMarker(
//            "ImGuiTableFlags_Borders\n = ImGuiTableFlags_BordersInnerV\n | ImGuiTableFlags_BordersOuterV\n | ImGuiTableFlags_BordersInnerV\n | ImGuiTableFlags_BordersOuterH");
//    ImGui::Indent();
//
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersH", &flags, ImGuiTableFlags_BordersH);
//    ImGui::Indent();
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterH", &flags, ImGuiTableFlags_BordersOuterH);
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerH", &flags, ImGuiTableFlags_BordersInnerH);
//    ImGui::Unindent();
//
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
//    ImGui::Indent();
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags, ImGuiTableFlags_BordersOuterV);
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags, ImGuiTableFlags_BordersInnerV);
//    ImGui::Unindent();
//
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuter", &flags, ImGuiTableFlags_BordersOuter);
//    ImGui::CheckboxFlags("ImGuiTableFlags_BordersInner", &flags, ImGuiTableFlags_BordersInner);
//    ImGui::Unindent();

//    ImGui::AlignTextToFramePadding();
//    ImGui::Text("Cell contents:");
//    ImGui::SameLine();
//    ImGui::RadioButton("Text", &contents_type, CT_Text);
//    ImGui::SameLine();
//    ImGui::RadioButton("FillButton", &contents_type, CT_FillButton);
//    ImGui::Checkbox("Display headers", &display_headers);
//    ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody);
//    ImGui::SameLine();
//    HelpMarker("Disable vertical borders in columns Body (borders will always appears in Headers");

    ///PopStyleCompact();
    ImGui::PopStyleVar(2);
    //Finish PopStyleCompact();

    if (ImGui::BeginTable("Table1", 4, flags)) {
        // Display headers so we can inspect their interaction with borders.
        // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)
        ImGui::TableSetupColumn("Fav", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort, 40);
        ImGui::TableSetupColumn("Pair", ImGuiTableColumnFlags_WidthStretch, 170);
        ImGui::TableSetupColumn("Last", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_NoResize, 90);
        ImGui::TableSetupColumn("24h", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoResize, 60);

        ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
        ImGui::TableHeadersRow();
        ImGui::PopStyleColor();

        for (auto filtered: filtered_symbols) {
            buildRow(*filtered.get()); //LV: ta certo?
        }

        ImGui::EndTable();
    }

//    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(5, 5));
//    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));
//
//    int tableFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX |
//                     ImGuiTableFlags_ScrollY;
//    if (ImGui::BeginTable("##table2", 2, tableFlags))
//    {
//        ImGui::TableSetupColumn("Asset", ImGuiTableColumnFlags_WidthStretch);
//        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);
//
//        for (int row = 0; row < 30; row++)
//        {
//            ImGui::TableNextRow();
//            ImGui::TableNextColumn();
//            cell();
//        }
//        ImGui::EndTable();
//    }
//    ImGui::PopStyleVar();
}

void StockSearch::buildRow(SymbolInfo info) {
    enum ContentsType {
        CT_Text, CT_FillButton
    };
    static int contents_type = CT_Text;

    ImGui::TableNextRow();

    //ImGui::BeginGroup();

    for (int column = 0; column < 4; column++) {
        ImGui::TableSetColumnIndex(column);

        if (column == 0) {
            ImGui::PushID(("##selectable_row" + info.name).c_str());
            if (ImGui::Selectable("##selectable_row", false,
                                  ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap,
                                  ImVec2(0, 0))) {
                printf("touched %s\n", info.name.c_str());
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

    //ImGui::EndGroup();


//    if(ImGui::IsItemHovered() && ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
//    }
}

void StockSearch::setFavoriteColumn(SymbolInfo info) {
    //adding the close button
    ImGui::PushID(("favorite_checkbox_" + info.name).c_str());
   // ImGui::Checkbox("##Checkbox1", &favorites[row_number]);

    Editor::Icons state = _favorites[info.name] ? Editor::Icons::fav_selected : Editor::Icons::fav_unselected;
    auto texture = getContext()->getEditor()->getTexture(state);

    if(ImGui::ImageButton((void*)(intptr_t)texture.my_image_texture, ImVec2(15, 15))){
        _favorites[info.name] = _favorites[info.name] ? false : true;
    }
    ImGui::PopID();

}

void StockSearch::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

