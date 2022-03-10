//
// Created by Luiz Veloso on 02/03/22.
//

#include "SubplotRenderer.h"

class SubplotRenderer;

SubplotRenderer::SubplotRenderer(Ticker *ticker)  {
    _ticker = ticker;
}

bool SubplotRenderer::onBeginRender() {
    //todo: size faz oq?
    return ImPlot::BeginPlot(getTitle(_title) , ImVec2(-1, 0), _flags);
}

const char* SubplotRenderer::getTitle(std::string name) const {
    return _title.c_str();
}

void SubplotRenderer::onEndRender() {
    ImPlot::EndPlot();
}

void SubplotRenderer::render() {
    onPreRender();
    if (onBeginRender()) {
        onSetupPlot();
        onRender();
        onDragDropTarget();
        onEndRender();
    }
    onPostRender();
}

void SubplotRenderer::onDragDropTarget() {
//    if (ImPlot::BeginDragDropTargetPlot()) {
//        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID)) {
//            //indice of dragged item
//            int i = *(int*)payload->Data;
//
//            puts("AGORA é a hora de plotar!!!");
//            getContext()->loadNewIndicator(IndicatorsView::CandleIndicatorsTypes(i), true);
//        }
//        ImPlot::EndDragDropTarget();
//    }
}

ImPlotSubplotFlags SubplotRenderer::getFlags() const {
    return _flags;
}

void SubplotRenderer::setFlags(ImPlotSubplotFlags flags) {
    _flags = flags;
}


void SubplotRenderer::addItemToPlot(std::shared_ptr<DataSeriesRenderer> item) {
    items.push_back(item);
}

void SubplotRenderer::removeItemFromPlot(std::shared_ptr<DataSeriesRenderer> item) {
    items.erase(std::remove(items.begin(), items.end(), item), items.end());
}

void SubplotRenderer::onRender() {
    for (auto& i: items) {
        i->render();
    }
}

void SubplotRenderer::updateRenderInterval(int startIndex, int endIndex) {
    _renderInterval.startIndex = startIndex;
    _renderInterval.endIndex = endIndex;

    for (auto& i : items) {
        i->updateRenderInterval(startIndex, endIndex);
    }
}

void SubplotRenderer::setTitle(const std::string &name) {
    _title = (_showTitle ? "" + name : "##" + name);
}

