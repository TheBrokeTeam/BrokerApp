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
    loadResources();

    // Initialize the context
    _context = std::make_shared<BackTestingContext>();

    _mainMenuBar = std::make_shared<MainMenuBar>(this);
    // Initialise Editor/ImGui
//    _widgets.emplace_back((this));

    _widgets.emplace_back(std::make_shared<DataLoader>(this));
    _widgets.emplace_back(std::make_shared<Charts>(this));


    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

void Editor::update() {
    //calculate deltime
    auto dt = getDeltaTime();

    _mainMenuBar->update(dt);
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
    getWidget<DataLoader>()->SetVisible(show);
}

void Editor::showCharts(bool show) {
    auto charts = getWidget<Charts>();
    if(charts)
        getWidget<Charts>()->SetVisible(show);
}

void Editor::showIndicators(bool show) {
    auto charts = getWidget<Charts>();
    if(charts)
        charts->enableIndicatorsOnCharts(show);
}

void Editor::loadResources() {
    int my_image_width = 0;
    int my_image_height = 0;
    GLuint my_image_texture = 0;

    bool ret = ImageLoader::loadTexture("../Resources/Icons/ma.png", &my_image_texture, &my_image_width, &my_image_height);

    ImageInfo info;
    info.my_image_width = my_image_width;
    info.my_image_height = my_image_height;
    info.my_image_texture = my_image_texture;

    _imagesRef.emplace(Icons::indicator_ma,info);

    IM_ASSERT(ret);
}

Editor::ImageInfo Editor::getTexture(Editor::Icons icon) {
    return _imagesRef.at(icon);
}

void Editor::showTabBars(bool show) {
    for(auto& w :_widgets){
        w->showTabBar(show);
    }
}

void Editor::showDockSpace()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
