//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "Indicators.h"
#include "../Editor.h"

Indicators::Indicators(Editor *editor) : Widget(editor) {

    for(int i = 0; i< _numberOfItems; i++)
        _dragAndDropItems.push_back(MyDndItem());
}

void Indicators::updateVisible(float dt) {
    Widget::updateVisible(dt);
    drawView();
    ImGui::SameLine();
}

void Indicators::drawView() {

    // child window to serve as initial source for our DND items
    ImGui::BeginChild("INDICATORS_ITEMS", ImVec2(100, 600));

    //button reset data
    if (ImGui::Button("Clear")) {
        for (int k = 0; k < _dragAndDropItems.size(); ++k)
            _dragAndDropItems[k].Reset();
//        dndx = dndy = NULL;
    }

    //add items to the view
    for (int k = 0; k < _dragAndDropItems.size(); ++k) {
        if (_dragAndDropItems[k].Plt > 0)
            continue;

        auto info = _editor->getTexture(Editor::Icons::indicator_ma);
        ImGui::BeginChild("##Icon Button");
        ImGui::ImageButton((void*)(intptr_t)info.my_image_texture, ImVec2(info.my_image_width*0.5, info.my_image_height*0.5));
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            ImGui::SetDragDropPayload(Indicators::CANDLE_INDICATORS, &k, sizeof(int));
            auto info = _editor->getTexture(Editor::Icons::indicator_ma);
            ImGui::Image((void*)(intptr_t)info.my_image_texture, ImVec2(info.my_image_width*0.5, info.my_image_height*0.5));
            ImGui::EndDragDropSource();
        }
        const bool hovered = ImGui::IsItemHovered();
        if (hovered) {
            puts("Mouse no indicador ICON");
        }
        ImGui::EndChild();

    }
    ImGui::EndChild();

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(Indicators::CANDLE_INDICATORS)) {
            int i = *(int *) payload->Data;
            _dragAndDropItems[i].Reset();
        }
        ImGui::EndDragDropTarget();
    }
}

//void CandleChart::showDemoDragAndDrop() {
//    ImGui::BulletText("Drag/drop items from the left column.");
//    ImGui::BulletText("Drag/drop items between plots.");
//    ImGui::Indent();
//    ImGui::BulletText("Plot 1 Targets: Plot, Y-Axes, Legend");
//    ImGui::BulletText("Plot 1 Sources: Legend Item Labels");
//    ImGui::BulletText("Plot 2 Targets: Plot, X-Axis, Y-Axis");
//    ImGui::BulletText("Plot 2 Sources: Plot, X-Axis, Y-Axis (hold Ctrl)");
//    ImGui::Unindent();



// child window to serve as initial source for our DND items
//    ImGui::BeginChild("DND_LEFT",ImVec2(100,600));
//
//    //button reset data
//    if (ImGui::Button("Reset Data")) {
//        for (int k = 0; k < _dragAndDropItems.size(); ++k)
//            _dragAndDropItems[k].Reset();
//        dndx = dndy = NULL;
//    }

//add items to the view
//    for (int k = 0; k < _dragAndDropItems.size(); ++k) {
//        if (_dragAndDropItems[k].Plt > 0)
//            continue;
//        ImPlot::ItemIcon(_dragAndDropItems[k].Color); ImGui::SameLine();
//        ImGui::Selectable(_dragAndDropItems[k].Label, false, 0, ImVec2(100, 0));
//        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
//            ImGui::SetDragDropPayload("MY_DND", &k, sizeof(int));
//            ImPlot::ItemIcon(_dragAndDropItems[k].Color); ImGui::SameLine();
//            ImGui::TextUnformatted(_dragAndDropItems[k].Label);
//            ImGui::EndDragDropSource();
//        }
//    }
//    ImGui::EndChild();
//
//    if (ImGui::BeginDragDropTarget()) {
//        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//            int i = *(int*)payload->Data;
//            _dragAndDropItems[i].Reset();
//        }
//        ImGui::EndDragDropTarget();
//    }
//
//    ImGui::SameLine();
//    ImGui::BeginChild("DND_RIGHT",ImVec2(-1,400));
//    // plot 1 (time series)
//    ImPlotAxisFlags flags = ImPlotAxisFlags_NoTickLabels | ImPlotAxisFlags_NoGridLines;
//    if (ImPlot::BeginPlot("##DND1", ImVec2(-1,195))) {
//        ImPlot::SetupAxis(ImAxis_X1, NULL, flags|ImPlotAxisFlags_Lock);
//        ImPlot::SetupAxis(ImAxis_Y1, "[drop here]", flags);
//        ImPlot::SetupAxis(ImAxis_Y2, "[drop here]", flags|ImPlotAxisFlags_Opposite);
//        ImPlot::SetupAxis(ImAxis_Y3, "[drop here]", flags|ImPlotAxisFlags_Opposite);
//
//        for (int k = 0; k < k_dnd; ++k) {
//            if (dnd[k].Plt == 1 && dnd[k].Data.size() > 0) {
//                ImPlot::SetAxis(dnd[k].Yax);
//                ImPlot::SetNextLineStyle(dnd[k].Color);
//                ImPlot::PlotLine(dnd[k].Label, &dnd[k].Data[0].x, &dnd[k].Data[0].y, dnd[k].Data.size(), 0, 2 * sizeof(float));
//                // allow legend item labels to be DND sources
//                if (ImPlot::BeginDragDropSourceItem(dnd[k].Label)) {
//                    ImGui::SetDragDropPayload("MY_DND", &k, sizeof(int));
//                    ImPlot::ItemIcon(dnd[k].Color); ImGui::SameLine();
//                    ImGui::TextUnformatted(dnd[k].Label);
//                    ImPlot::EndDragDropSource();
//                }
//            }
//        }
//        // allow the main plot area to be a DND target
//        if (ImPlot::BeginDragDropTargetPlot()) {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = ImAxis_Y1;
//            }
//            ImPlot::EndDragDropTarget();
//        }
//        // allow each y-axis to be a DND target
//        for (int y = ImAxis_Y1; y <= ImAxis_Y3; ++y) {
//            if (ImPlot::BeginDragDropTargetAxis(y)) {
//                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                    int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = y;
//                }
//                ImPlot::EndDragDropTarget();
//            }
//        }
//        // allow the legend to be a DND target
//        if (ImPlot::BeginDragDropTargetLegend()) {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                int i = *(int*)payload->Data; dnd[i].Plt = 1; dnd[i].Yax = ImAxis_Y1;
//            }
//            ImPlot::EndDragDropTarget();
//        }
//        ImPlot::EndPlot();
//    }
//    // plot 2 (Lissajous)
//    if (ImPlot::BeginPlot("##DND2", ImVec2(-1,195))) {
//        ImPlot::PushStyleColor(ImPlotCol_AxisBg, dndx != NULL ? dndx->Color : ImPlot::GetStyle().Colors[ImPlotCol_AxisBg]);
//        ImPlot::SetupAxis(ImAxis_X1, dndx == NULL ? "[drop here]" : dndx->Label, flags);
//        ImPlot::PushStyleColor(ImPlotCol_AxisBg, dndy != NULL ? dndy->Color : ImPlot::GetStyle().Colors[ImPlotCol_AxisBg]);
//        ImPlot::SetupAxis(ImAxis_Y1, dndy == NULL ? "[drop here]" : dndy->Label, flags);
//        ImPlot::PopStyleColor(2);
//        if (dndx != NULL && dndy != NULL) {
//            ImVec4 mixed((dndx->Color.x + dndy->Color.x)/2,(dndx->Color.y + dndy->Color.y)/2,(dndx->Color.z + dndy->Color.z)/2,(dndx->Color.w + dndy->Color.w)/2);
//            ImPlot::SetNextLineStyle(mixed);
//            ImPlot::PlotLine("##dndxy", &dndx->Data[0].y, &dndy->Data[0].y, dndx->Data.size(), 0, 2 * sizeof(float));
//        }
//        // allow the x-axis to be a DND target
//        if (ImPlot::BeginDragDropTargetAxis(ImAxis_X1)) {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                int i = *(int*)payload->Data; dndx = &dnd[i];
//            }
//            ImPlot::EndDragDropTarget();
//        }
//        // allow the x-axis to be a DND source
//        if (dndx != NULL && ImPlot::BeginDragDropSourceAxis(ImAxis_X1)) {
//            ImGui::SetDragDropPayload("MY_DND", &dndx->Idx, sizeof(int));
//            ImPlot::ItemIcon(dndx->Color); ImGui::SameLine();
//            ImGui::TextUnformatted(dndx->Label);
//            ImPlot::EndDragDropSource();
//        }
//        // allow the y-axis to be a DND target
//        if (ImPlot::BeginDragDropTargetAxis(ImAxis_Y1)) {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                int i = *(int*)payload->Data; dndy = &dnd[i];
//            }
//            ImPlot::EndDragDropTarget();
//        }
//        // allow the y-axis to be a DND source
//        if (dndy != NULL && ImPlot::BeginDragDropSourceAxis(ImAxis_Y1)) {
//            ImGui::SetDragDropPayload("MY_DND", &dndy->Idx, sizeof(int));
//            ImPlot::ItemIcon(dndy->Color); ImGui::SameLine();
//            ImGui::TextUnformatted(dndy->Label);
//            ImPlot::EndDragDropSource();
//        }
//        // allow the plot area to be a DND target
//        if (ImPlot::BeginDragDropTargetPlot()) {
//            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("MY_DND")) {
//                int i = *(int*)payload->Data; dndx = dndy = &dnd[i];
//            }
//        }
//        // allow the plot area to be a DND source
//        if (ImPlot::BeginDragDropSourcePlot()) {
//            ImGui::TextUnformatted("Yes, you can\ndrag this!");
//            ImPlot::EndDragDropSource();
//        }
//        ImPlot::EndPlot();
//    }
//    ImGui::EndChild();
//}


std::vector<Indicators::MyDndItem> &Indicators::getIndicators() {
    return _dragAndDropItems;
}
