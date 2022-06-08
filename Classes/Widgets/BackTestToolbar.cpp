//
// Created by Arthur Abel Motelevicz on 25/05/22.
//

#include "BackTestToolbar.h"
#include "../Editor.h"
#include "../Contexts/BackTestingContext.h"

BackTestToolbar::BackTestToolbar(Context* context) : Widget(context){
    _title                  = "BACKTEST";
    _is_window              = false;
    _context = dynamic_cast<BackTestingContext*>(context);
}

void BackTestToolbar::updateAlways(float dt) {
    ToolbarUI();
}

void BackTestToolbar::ToolbarUI()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, BrokerMenuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, BrokerToolBarHeight));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0
                                    | ImGuiWindowFlags_NoDocking
                                    | ImGuiWindowFlags_NoTitleBar
                                    | ImGuiWindowFlags_NoResize
                                    | ImGuiWindowFlags_NoMove
                                    | ImGuiWindowFlags_NoScrollbar
                                    | ImGuiWindowFlags_NoSavedSettings;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(GetPadding(), GetPadding()));
    ImGui::PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);

    ImGui::Begin("TOOLBAR", NULL, window_flags);

    ImGui::TextColored(Editor::broker_white,_title.c_str());

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));

    ImGui::PushStyleColor(ImGuiCol_Button, Editor::broker_black);
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_very_very_light_grey);

    //### BUTTONS
    ImGui::PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_very_light_grey);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_light_grey);

    float buttonPadding = BrokerToolBarButtonSide*0.1f;
    float posY = buttonPadding;
    float widthBtn = BrokerToolBarButtonSide - buttonPadding*2;

    //SPEED
    float posX = ImGui::GetWindowWidth() - BrokerToolBarButtonSide - buttonPadding;

    static int selectedIdx = 0;
    const char* items[] = { "1x", "2x", "3x", "4x", "5x", "6x", "7x", "8x", "9x", "10x" };
    static int item_current_idx = 0;
    const char* combo_preview_value = items[item_current_idx];

    //items colors
    ImGui::PushStyleColor(ImGuiCol_Header,Editor::broker_black);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive,Editor::broker_very_light_grey);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered,Editor::broker_light_grey);

    addButton(combo_preview_value,posX,posY,widthBtn,[&](){
        std::cout << "Click Dummy" << std::endl;
        ImGui::OpenPopup("speed_popup");
    });

    if (ImGui::BeginPopup("speed_popup")){
        ImGui::Text("%s", combo_preview_value);
        ImGui::Separator();
        for (int i = 0; i < IM_ARRAYSIZE(items); i++)
            if (ImGui::Selectable(items[i])) {
                item_current_idx = i;
                _currentSpeedX = i + 1;
                onClick(Click::CHANGE_SPEED);
            }
        ImGui::EndPopup();
    }
    ImGui::PopStyleColor(3);

    //--------
    

    //change font for small icons
    ImGuiIO &io = ImGui::GetIO();
    //icons at size 12
    ImFont* font = io.Fonts->Fonts[5];
    ImGui::PushFont(font);

    //PLAY-STOP
    posX = ImGui::GetWindowWidth() - BrokerToolBarButtonSide*3 - buttonPadding*3;
    addButton(_playing ? ICON_FA_STOP : ICON_FA_PLAY,posX,posY,widthBtn,[&](){
        if(_playing) {
            std::cout << "Click Stop" << std::endl;
            onClick(Click::STOP);
        }
        else{
            std::cout << "Click Play" << std::endl;
            onClick(Click::PLAY);
        }
        _playing = !_playing;
    });
    //--------

    //PAUSE
    posX = ImGui::GetWindowWidth() - BrokerToolBarButtonSide*2 - buttonPadding*2;
    addButton(ICON_FA_PAUSE,posX,posY,widthBtn,[&](){
        std::cout << "Click Pause" << std::endl;
        onClick(Click::PAUSE);
    });
    //--------


    ImGui::PopStyleColor(4);
    ImGui::PopFont();
    ImGui::PopStyleVar();
    //### END BUTTONS


    ImGui::End();

    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);
}

void BackTestToolbar::addButton(const char* icon, float xPos, float yPos, float width, std::function<void()> callback){
    ImGui::SameLine();
    ImGui::SetCursorPosX(xPos);
    ImGui::SetCursorPosY(yPos);
    if (ImGui::Button(icon,ImVec2(width,width))){
        callback();
    }
}
int BackTestToolbar::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void BackTestToolbar::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void BackTestToolbar::setClickCallback(ClickCallback c){
    _clickCallback = c;
}

void BackTestToolbar::onClick(Click src) {
    if(_clickCallback)
        _clickCallback(src);

    switch (src) {
        case Click::PLAY:
            puts("Clicou no botão play!!!");
            _context->startSimulation(nullptr);
            break;
        case Click::STOP:
            puts("Clicou no botão stop!!!");
            _context->stopSimulation();
            break;
        case Click::PAUSE:
            puts("Clicou no botão pause!!!");
            _context->pauseSimulation();
            break;
        case Click::CHANGE_SPEED:
            puts("Mudou speed!!!");
            _context->setSimulationSpeed(_currentSpeedX);
            break;
        default:
            break;
    }
}

