//
// Created by Luiz Veloso on 05/03/22.
//

#include "NewChartView.h"
#include "BrokerColorsImgui.h"
#include "MainChartRenderer.h"
NewChartView::NewChartView(Context *context) : Widget(context)
{
    _title                  = "New Chart View";
    _is_window              = true;

    addSlider();
}

void NewChartView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    if(_chart != nullptr)
        _chart->render();

    if(_slider != nullptr)
        _slider->updateVisible(dt);
}

void NewChartView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,BrokerColorsImgui::broker_dark_grey);
}

void NewChartView::addSlider() {
   _slider = std::make_shared<ChartSliderView>(context);
   _slider->setDelegate(this);
}

void NewChartView::addChart(std::shared_ptr<ChartRenderer> chartRenderer){
    _chart.reset();
    _chart = std::move(chartRenderer);
    _chart->setDelegate(this);
}

void NewChartView::sliderDidScroll(float value) {
    printf("\n -> ChartSliderDELEGATE called");

    int posIdxMax = int((_chart->_ticker->getBarHistory()->size() - 1) * value);
    int posIdxMin = posIdxMax - _chart->_ticker->getMaxBarsToRender() < 0 ? 0 : posIdxMax - _chart->_ticker->getMaxBarsToRender();

    double movedMin = _chart->_ticker->getBarHistory()->getData(BarDataType::TIME)[posIdxMin];
    double movedMax = _chart->_ticker->getBarHistory()->getData(BarDataType::TIME)[posIdxMax];

    _chart->updateRenderInterval(posIdxMin, posIdxMax);
}

void NewChartView::chartDidScroll(int lastVisibleIndex) {
    printf("\n -> ChartRendererDELEGATE called");
    float posPercent = float(lastVisibleIndex+1)/float(_chart->_ticker->getBarHistory()->size());
    _slider->setPositionValue(posPercent);

}
