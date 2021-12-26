//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "Widgets/MainMenuBar.h"
#include "Widgets/Workspace.h"
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

    // Initialise Editor/ImGui
    _widgets.emplace_back(std::make_shared<MainMenuBar>(this));
    _widgets.emplace_back(std::make_shared<Workspace>(this));

    _widgets.emplace_back(std::make_shared<DataLoader>(this));
    _widgets.emplace_back(std::make_shared<Charts>(this));


    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}


void Editor::BeginWindow() {
    // Set window flags

    // Begin dock space
//    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    const auto window_flags =
            ImGuiWindowFlags_MenuBar               |
            ImGuiWindowFlags_NoDocking             |
            ImGuiWindowFlags_NoTitleBar            |
            ImGuiWindowFlags_NoCollapse            |
            ImGuiWindowFlags_NoResize              |
            ImGuiWindowFlags_NoMove                |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;

    // Set window position and size
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y));
    ImGui::SetNextWindowViewport(viewport->ID);

    // Set window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowBgAlpha(0.0f);

    // Begin window
    std::string name = "##main_window";
    bool open = true;
    _editor_begun = ImGui::Begin(name.c_str(), &open, window_flags);
    ImGui::PopStyleVar(3);
}

void Editor::update() {
    //calculate deltime
    auto dt = getDeltaTime();

    // Editor - Begin
    BeginWindow();

    // Editor - update widgets
    for (std::shared_ptr<Widget>& widget : _widgets)
    {
        widget->update(dt);
    }

    // Editor - End
    if (_editor_begun)
        ImGui::End();
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
    getWidget<Charts>()->SetVisible(show);
}

void Editor::showIndicators(bool show) {
    getWidget<Charts>()->enableIndicatorsOnCharts(show);
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

int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
