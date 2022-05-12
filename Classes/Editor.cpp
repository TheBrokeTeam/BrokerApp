//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Editor.h"
#include <GLFW/glfw3.h>
#include <imgui.h>
#include "Contexts/BackTestingContext.h"
#include "Contexts/LiveContext.h"
#include "Helpers/ImageLoader.h"

void Editor::start() {

    //loading images
    loadImage(Icons::indicator_ma,"../Resources/Icons/ma.png");
    loadImage(Icons::close_window,"../Resources/Icons/close.png");
    loadImage(Icons::trash,"../Resources/Icons/trash.png");

    //node icons white
    loadImage(Icons::node_bar_seq_down,"../Resources/Icons/node_bar_seq_down_w.png");
    loadImage(Icons::node_bar_seq_up,"../Resources/Icons/node_bar_seq_up_w.png");
    loadImage(Icons::node_counter,"../Resources/Icons/node_counter_w.png");
    loadImage(Icons::node_cross,"../Resources/Icons/node_cross_w.png");
    loadImage(Icons::node_trend,"../Resources/Icons/node_trend_w.png");
    loadImage(Icons::node_trade,"../Resources/Icons/node_trade_w.png");

    //node icons black
    loadImage(Icons::node_bar_seq_down_black,"../Resources/Icons/node_bar_seq_down.png");
    loadImage(Icons::node_bar_seq_up_black,"../Resources/Icons/node_bar_seq_up.png");
    loadImage(Icons::node_counter_black,"../Resources/Icons/node_counter.png");
    loadImage(Icons::node_cross_black,"../Resources/Icons/node_cross.png");
    loadImage(Icons::node_trend_black,"../Resources/Icons/node_trend.png");
    loadImage(Icons::node_trade_black,"../Resources/Icons/node_trade.png");


    //favoriteIcons
    loadImage(Icons::fav_unselected, "../Resources/Icons/fav_unselected.png");
    loadImage(Icons::fav_selected, "../Resources/Icons/fav_selected.png");

    //garbageBin
    loadImage(Icons::garbage_bin, "../Resources/Icons/garbage_bin.png");

    //----------------------------------------------
    //this way is the logic to change the context now
    // and not at the begining of the next frame
    _nextContextType = Editor::ContextType::BackTesting;
    internalLoadContext();
    //----------------------------------------------

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
    //check if the context should change
    if(shouldReloadContext)
        internalLoadContext();

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
//    float dt = currentTime -_lastTime;
//TODO:: fixing in 16 ms to avoid issues when debugging
    float dt = 0.01666;
//    _lastTime = currentTime;
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

void Editor::loadContext(Editor::ContextType type)
{
    if(type == _contextType) return;
    _nextContextType = type;
    shouldReloadContext = true;
}

void Editor::internalLoadContext()
{
    _contextType = _nextContextType;
    _nextContextType = ContextType::None;

    _context.reset();
    switch (_contextType) {
        case  Editor::ContextType::LiveTrade:
            _context = std::make_unique<LiveContext>(this);
            break;
        case  Editor::ContextType::BackTesting:
            _context = std::make_unique<BackTestingContext>(this);
            break;
        case Editor::ContextType::None:
        default:
            assert(false && "Broker app context not set!");
            break;
    }
    _context->initialize();
    shouldReloadContext = false;
}

const Editor::ContextType& Editor::getContextType() {
    return _contextType;
}

Editor::~Editor() {}


//APPLICATION ENTRY POINT
int main(int argc, char const* argv[]){
    Editor app("",600,400,argc,argv);
    app.run();
}
