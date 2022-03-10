//
// Created by Luiz Veloso on 05/03/22.
//

#include "ChartSliderView.h"
#include "BrokerColorsImgui.h"

ChartSliderView::ChartSliderView(Context *context) : Widget(context) {
    _title = "Chart Slider";
    _is_window = false;
}

void ChartSliderView::updateVisible(float dt) {
    Widget::updateVisible(dt);
    render();
}

void ChartSliderView::onPushStyleVar() {
    Widget::onPushStyleVar();
}

void ChartSliderView::render() {//SliderStuff
    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - 16);
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, BrokerColorsImgui::broker_yellow_active);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, BrokerColorsImgui::broker_yellow);
    ImGui::PushStyleColor(ImGuiCol_FrameBg, BrokerColorsImgui::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, BrokerColorsImgui::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, BrokerColorsImgui::broker_light_grey);


    if(ImGui::SliderFloat("##Slider", &_positionValue, 0.000f, 1.000f, "%.3f")){
        printf("sliderDidScroll");

        if(_delegate != nullptr)
            _delegate->sliderDidScroll(_positionValue);
//        int posIdxMax = int((dataHist.size() - 1) * _positionValue);
//        int posIdxMin = posIdxMax - _ticker->getMaxBarsToRender() < 0 ? 0 : posIdxMax - _ticker->getMaxBarsToRender();
//
//        movedMin = dataHist.getData(TIME)[posIdxMin];
//        movedMax = dataHist.getData(TIME)[posIdxMax];
//        forceChangeMax =  true;
    }
    else{
        //update postioner
//        float posPercent = float(_lastIdxX + 1) / dataHist.size();
//        _positionValue = posPercent;
    }

    ImGui::PopStyleColor(5);
}

void ChartSliderView::setDelegate(ChartSliderDelegate *delegate) {
    ChartSliderView::_delegate = delegate;
}

void ChartSliderView::setPositionValue(float positionValue) {
    _positionValue = positionValue;
}
