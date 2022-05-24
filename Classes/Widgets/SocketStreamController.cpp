//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketStreamController.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Common/Json/BAJson.h"

SocketStreamController::SocketStreamController(Context* context) : Widget(context)
{
    _title = "SS Controller";
    _is_window = true;

    //TODO:: this should be automatic when on live context
    _symbol =   Symbol(_symbolName,"1m",0,0);
    getContext()->openSymbolStream(_symbol);
    _oldSymbolName = _symbolName;

    //TODO:: the user data stream should open automatic when the user already set his keys
    getContext()->openUserDataStream();
}

void SocketStreamController::updateVisible(float dt)
{
    Widget::updateVisible(dt);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_white);

    static char buff[8] = "ETHUSDT";
    ImGui::SetNextItemWidth(200);
    if (ImGui::InputText("##Symbol",buff,8,ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_EnterReturnsTrue)) {
        _symbolName = buff;
        changeStream();
    }

    ImGui::SetNextItemWidth(80);

    static int interval = 0;

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Interval");

    ImGui::SetNextItemWidth(110);

    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    static float amountToTrade = 0.006;


    if (ImGui::Button("Comprar",ImVec2(200,50))) {
        if(auto st = _strategy.lock())
            st->openPosition(false,amountToTrade);
    }

    if (ImGui::Button("Vender",ImVec2(200,50))) {
        if(auto st = _strategy.lock())
            st->openPosition(true,amountToTrade);
    }

    ImGui::SliderFloat("Amount",&amountToTrade,0.004,0.01,"%.4f",ImGuiSliderFlags_None);

    ImGui::Dummy(ImVec2(0,40));


    if(auto st = _strategy.lock()) {
        if(!st->getOpenedPositions().empty())
        if (ImGui::Button("Close First Position", ImVec2(200, 50))) {
            if (auto st = _strategy.lock())
                st->openPosition(true);
        }
    }


//    if (ImGui::Button("Cancelar ordens abertas",ImVec2(200,50))) {
//        getContext()->closeAllOrders(_symbol);
//    }
}

int SocketStreamController::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void SocketStreamController::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void SocketStreamController::changeStream() {
    getContext()->closeSymbolStream(Symbol(_oldSymbolName,"1m",0,0));
    _symbol =   Symbol(_symbolName,"1m",0,0);
    getContext()->openSymbolStream(_symbol);
    _oldSymbolName = _symbolName;
}

void SocketStreamController::testFunction() {
    auto jsonPath = "../Resources/test_data.json";

    rapidjson::Document document;
    if (!BAJson::parseFile(jsonPath, document)) {
        std::cout << "NAo rolou ler json" << std::endl;
    }
    else{
        std::cout << BAJson::stringfy(document) << std::endl;

        BAJson::save(document,"../Resources/tato.json");
    }
}

void SocketStreamController::setStrategyTest(std::weak_ptr<Strategy> strategy) {
    _strategy = strategy;
}
