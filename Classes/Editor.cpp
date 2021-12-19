//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_internal.h>
#include "Widgets/Widget_MainMenuBar.h"
#include "Contexts/Context.h"

namespace _editor
{

}

void Editor::start() {
    // Initialize the context
    _context = std::make_shared<BrokerApp::Context>();

    // Initialise Editor/ImGui
    _widgets.emplace_back(std::make_shared<Widget_MainMenuBar>(this));

    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}


void Editor::BeginWindow() {
    // Set window flags

    // Begin dock space
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

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


Editor::~Editor() {}

int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
