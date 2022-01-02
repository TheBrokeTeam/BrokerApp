//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "TestNode.h"
#include <imgui.h>
#include <imnodes.h>

#include "../../Editor.h"

TestNode::TestNode() {
    _id = ++current_id;
    _idInput = ++current_id;
    _idOutput = ++current_id;
}

void TestNode::render() {
//
    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));


    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));


    ImNodes::BeginNode(_id);

    ImNodes::BeginNodeTitleBar();
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_black);
    ImGui::Text("simple node :)");
    //allow candles plot area to be a DRAG AND DROP target ##
    if (ImGui::BeginDragDropTarget()) {

        //######################################################
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CANDLE_INDICATOR")) {
            //indice of dragged item
            int i = *(int *) payload->Data;

            puts("AGORA é a hora de plotar!!!");
//                _open_popup = true;
        }
        ImGui::EndDragDropTarget();
    }
    ImGui::PopStyleColor();
    ImNodes::EndNodeTitleBar();


    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImNodes::EndInputAttribute();

    ImGui::SameLine();
    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(40);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();

    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();



}

