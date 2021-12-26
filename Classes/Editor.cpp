//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "Widgets/MainMenuBar.h"
#include "Widgets/DataLoader.h"
#include "Widgets/Charts.h"

#include "Contexts/BackTestingContext.h"
#include "Widget+Tickables/CandleChart.h"
#include "Tickers/Ticker.h"
#include "Helpers/ImageLoader.h"

void Editor::start() {

    //loading images
    loadImage(Icons::indicator_ma,"../Resources/Icons/ma.png");
    loadImage(Icons::close_window,"../Resources/Icons/close.png");

    // Initialize the context
    _context = std::make_shared<BackTestingContext>();

    _widgets.emplace_back(std::make_shared<MainMenuBar>(this));
    _widgets.emplace_back(std::make_shared<DataLoader>(this));
    _widgets.emplace_back(std::make_shared<Charts>(this));

    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

void Editor::update() {
    //calculate deltime
    auto dt = getDeltaTime();

    showDockSpace();

    // Editor - update widgets
    for (std::shared_ptr<Widget>& widget : _widgets)
    {
        widget->update(dt);
    }
}

float Editor::getDeltaTime(){
    auto currentTime = glfwGetTime();
    float dt = currentTime -_lastTime;
    _lastTime = currentTime;
    return dt;
}

Context* Editor::getContext(){
    return _context.get();
}

Editor::~Editor() {}

void Editor::addChartWidget(Ticker *ticker) {
    auto charts = getWidget<Charts>();
    charts->addChart(std::make_shared<CandleChart>(this,ticker));
    _context->loadTicker(*ticker->getSymbol());
}

void Editor::showDataLoader(bool show) {
    auto donwloader = getWidget<DataLoader>();
    if(donwloader)
        donwloader->SetVisible(show);

    MainMenuBar::_show_downloader = show;
}

void Editor::showCharts(bool show) {
    auto charts = getWidget<Charts>();
    if(charts)
        getWidget<Charts>()->SetVisible(show);

    MainMenuBar::_show_charts = show;

}

void Editor::showIndicators(bool show) {
    auto charts = getWidget<Charts>();
    if(charts)
        charts->enableIndicatorsOnCharts(show);

    MainMenuBar::_show_indicators = show;
}

void Editor::loadImage(Icons icon,const std::string& filepath)
{
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;

    bool ret = ImageLoader::loadTexture(filepath.c_str() , &my_image_texture, &my_image_width, &my_image_height);

    IM_ASSERT(ret);

    ImageInfo info;
    info.my_image_width = my_image_width;
    info.my_image_height = my_image_height;
    info.my_image_texture = my_image_texture;

    _imagesRef.emplace(icon,info);
}

Editor::ImageInfo Editor::getTexture(Editor::Icons icon) {
    return _imagesRef.at(icon);
}

void Editor::showTabBars(bool show) {
    for(auto& w :_widgets){
        w->showTabBar(show);
    }
    MainMenuBar::_show_tabbars = show;
}

void Editor::showDockSpace()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
