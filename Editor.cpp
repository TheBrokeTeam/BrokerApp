//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>

void Editor::start() {

    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

//    //initialize listener and subscribe to all ui actions
//    _listener = std::make_unique<Listener>(_bus);
//    _listener->listen<ui_event::FetchButtonClicked>(std::bind(&Editor::fetchData,this,std::placeholders::_1));
//
//    //create ui manager passing the bus to notify all listeners above
//    _uiManager = std::make_unique<UIManager>( _bus);
//    _dataManager = std::make_unique<DataManager>( _bus);
}

void Editor::update() {
    auto dt = getDeltaTime();
//    _uiManager->update(dt);
//    _bus->process();
}

float Editor::getDeltaTime(){
    auto currentTime = glfwGetTime();
    float dt = currentTime -_lastTime;
    _lastTime = currentTime;
    return dt;
}

//void Editor::fetchData(const ui_event::FetchButtonClicked &event) {
//    auto info = event.info;
//    std::cout << "Fecth clicked : " << info.fetchInterVal << std::endl;
//    std::cout << info.fetchMonth << std::endl;
//    std::cout << info.fetchSymbol << std::endl;
//    std::cout << info.fetchYear << std::endl;
//}

Editor::~Editor() {
    //unsubscribe all listeners
//    _listener->unlistenAll();
}

int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
