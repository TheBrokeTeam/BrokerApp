//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Contexts/BackTestingContext.h"
#include "Helpers/ImageLoader.h"

void Editor::start() {

    //loading images
    loadImage(Icons::indicator_ma,"../Resources/Icons/ma.png");
    loadImage(Icons::close_window,"../Resources/Icons/close.png");
    loadImage(Icons::trash,"../Resources/Icons/trash.png");
    loadImage(Icons::node_bar_seq_down,"../Resources/Icons/node_bar_seq_down_w.png");
    loadImage(Icons::node_bar_seq_up,"../Resources/Icons/node_bar_seq_up_w.png");
    loadImage(Icons::node_counter,"../Resources/Icons/node_counter_w.png");
    loadImage(Icons::node_cross,"../Resources/Icons/node_cross_w.png");
    loadImage(Icons::node_trend,"../Resources/Icons/node_trend_w.png");
    loadImage(Icons::node_trade,"../Resources/Icons/node_trade_w.png");

    _context = std::make_shared<BackTestingContext>(this);

    _context->initialize();

    //enable the docking on this application
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    io.AddInputCharacter(GLFW_KEY_DELETE);

    auto& style = ImGui::GetStyle();

    style.Colors[ImGuiCol_Separator] = Editor::broker_black;
    style.Colors[ImGuiCol_SeparatorHovered] = Editor::broker_yellow;
    style.Colors[ImGuiCol_SeparatorActive] = Editor::broker_yellow;

    //TODO:: make a way to change the layout configuration at run time
    ImGui::LoadIniSettingsFromDisk("ui_num_1");
}

void Editor::update() {
    //calculate deltime
    auto dt = getDeltaTime();

    //update data context first
    _context->updateData(dt);

    //call docking behavior
    showDockSpace();

    //update widgets
    _context->updateUI(dt);
}

float Editor::getDeltaTime(){
    auto currentTime = glfwGetTime();
    float dt = currentTime -_lastTime;
    _lastTime = currentTime;
    return dt;
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


void Editor::showDockSpace()
{
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

Editor::~Editor() {}

//APPLICATION ENTRY POINT
int main(int argc, char const* argv[]){
    Editor app("",1400,750,argc,argv);
    app.run();
}
