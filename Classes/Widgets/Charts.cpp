//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Charts.h"

Charts::Charts(Editor *editor) : Widget(editor) {
    _title                  = "Charts";
    _is_window              = true;
}

void Charts::updateVisible(float dt) {
    ImGui::SetNextItemWidth(400);
    if (ImGui::BeginTabBar("Symbols")) {

        ImGui::EndTabBar();
    }

}
