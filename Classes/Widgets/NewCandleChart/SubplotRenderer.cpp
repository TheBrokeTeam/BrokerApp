//
// Created by Luiz Veloso on 02/03/22.
//

#include "SubplotRenderer.h"


SubplotRenderer::SubplotRenderer(Ticker* ticker)  {
    _ticker = ticker;
}

bool SubplotRenderer::onBeginRender() {
    //todo: size faz oq?
    return ImPlot::BeginPlot(getTitle(_title) , ImVec2(-1, 0), _flags);
}

const char* SubplotRenderer::getTitle(std::string name) const {
    return ((_showTitle ? "" : "##") + name).c_str();
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
//
//int SubplotRenderer::getLastIdxX() const {
//    return _ticker->getBarHistory()->size() - 1;
//}
//
//int SubplotRenderer::getLastIdxToPlot() const {
//    int numberOfBarsToRender = _ticker->getBarHistory()->size() > _ticker->getMaxBarsToRender() ? _ticker->getMaxBarsToRender() : _ticker->getBarHistory()->size();
//    return _lastIdxX - numberOfBarsToRender  < 0  ? 0 :  _lastIdxX - numberOfBarsToRender ;
//}


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



