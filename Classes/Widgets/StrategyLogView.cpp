////
//// Created by Maykon Meneghel on 26/04/22.
////
//
//#include "StrategyLogView.h"
//#include "../Editor.h"
//#include "../Contexts/BackTestingContext.h"
//
//StrategyLogView::StrategyLogView(Context *context) : Widget(context) {
//    _title                  = "Logs";
//    _is_window              = true;
//    _headers = std::list<std::string>({"updatedAt", "name", "code", "interval", "nodes"});
//}
//
//void StrategyLogView::updateVisible(float dt) {
//    Widget::updateVisible(dt);
//
//    static ImGuiTableFlags flags =  ImGuiTableFlags_ScrollY         |
//                                    ImGuiTableFlags_RowBg           |
//                                    ImGuiTableFlags_BordersOuter    |
//                                    ImGuiTableFlags_Reorderable     |
//                                    ImGuiTableColumnFlags_WidthFixed |
//                                    ImGuiTableFlags_NoPadOuterX
//                                    ;
//
//    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
//    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
//    if (ImGui::BeginTable("table_advanced", int(_headers.size()), flags, outer_size))
//    {
//        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
//
//        for(const auto& header: _headers) {
//            ImGui::TableSetupColumn(header.c_str(), ImGuiTableColumnFlags_None);
//        }
//
//        ImGui::TableHeadersRow();
//
//        if(getContext()->userSelected()) {
//
//            for(auto& bot: getContext()->getBots()) {
//
//                ImGui::TableNextRow();
//
//                ImGui::TableSetColumnIndex(0);
//
//                if (ImGui::Selectable(bot.GetName().c_str(), false, ImGuiSelectableFlags_SelectOnClick | ImGuiSelectableFlags_SpanAllColumns)) {
//                    std::cout << "User select the " << bot.GetName().c_str()  << "bot." << std::endl;
//                    getContext()->selectBot(bot);
//                }
//
//                ImGui::TableSetColumnIndex(1);
//                ImGui::Text("%s", bot.GetUpdatedTime().c_str());
//
//                Symbol s = bot.GetSymbol();
//                ImGui::TableSetColumnIndex(2);
//                ImGui::Text("%s", s.getCode().c_str());
//
//                ImGui::TableSetColumnIndex(3);
//                ImGui::Text("%s", s.getInterval().c_str());
//
//                ImGui::TableSetColumnIndex(4);
//                for(auto& node: bot.GetNodes()) {
//                    ImGui::Text("%s", node.name.c_str());
//                }
//
//            }
//        } else {
//            ImGui::TableNextRow();
//            ImGui::TableSetColumnIndex(0);
//            std::string message = "No records found";
//            ImGui::Text("%s", message.c_str());
//        }
//
//        ImGui::EndTable();
//    }
//
//}
//
//int StrategyLogView::getWindowFlags() {
//    return Widget::getWindowFlags();
//}
//
//void StrategyLogView::onPushStyleVar() {
//    Widget::onPushStyleVar();
//}
