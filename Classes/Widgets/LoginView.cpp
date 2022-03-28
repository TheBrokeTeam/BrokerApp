//
// Created by Maykon Meneghel on 09/02/22.
//

#include "LoginView.h"

LoginView::LoginView(Context *context) : Widget(context) {
    _title = "Profile";
    _is_window = true;
}

void LoginView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if(getContext()->_finishedAuthentication) {

        PushStyleColor(ImGuiCol_Text, Editor::broker_white);
        ImGui::Text("Hi, stranger");

    } else {
        // change color text
        PushStyleColor(ImGuiCol_Text,Editor::broker_black);

        if (ImGui::Button("Log In",ImVec2(200,50)))
        {
            puts("Clicou em login!!!");
            getContext()->_startingAuthentication = true;
        }

        if(getContext()->_startingAuthentication) {
            ImVec2 windowSize = getContext()->getEditor()->getWindowSize();
            ImVec2 blackoutSize = ImVec2(windowSize.x, windowSize.y);
            ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2 - blackoutSize.x / 2, windowSize.y / 2 - blackoutSize.y / 2),
                                    ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(blackoutSize, ImGuiCond_FirstUseEver);

            PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f,0.0f, 0.80f));

            if (ImGui::Begin("Blackout", NULL,(
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize |
                    ImGuiWindowFlags_NoMouseInputs
            ))){}
            ImGui::End();

            ImVec2 modalSize = ImVec2(250, 500);
            ImGui::SetNextWindowPos(ImVec2(windowSize.x / 2 - modalSize.x / 2, windowSize.y / 2 - modalSize.y / 2),
                                    ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(modalSize, ImGuiCond_FirstUseEver);

            PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f,0.0f, 1.00f));

            if (ImGui::Begin("SignInPopPup", NULL,(
                    ImGuiWindowFlags_NoMove |
                    ImGuiWindowFlags_NoTitleBar |
                    ImGuiWindowFlags_NoScrollbar |
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize
            )))
            {
                if(getContext()->_sentAuthentication)
                {
                    const ImVec4 col = ImVec4(0.94f, 0.72f, 0.02f, 1.00f);
                    const ImVec4 bg = ImVec4(0.86f, 0.11f, 0.71f, 1.00f);
                    ImGui::SetCursorPos(ImVec2(modalSize.x / 2 - 5, modalSize.y / 2 - 5));
                    ImGui::LoadingIndicatorCircle("Waiting", 10, bg, col, 12, 10);

                    ImVec2 buttonSize = ImVec2(0.80f*(modalSize.x), 35);
                    ImGui::Dummy(ImVec2((modalSize.x), 50));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Cancel",buttonSize))
                    {
                        LoginView::Cancel();
                    }
                }
                else {
                    ImVec2 buttonSize = ImVec2(0.80f*(modalSize.x), 35);

                    ImGui::Dummy(ImVec2((modalSize.x), 200));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Log In with Facebook", buttonSize))
                    {
                        puts("Facebook");
                        this->openAuthProvider("facebook");
                    }

                    ImGui::Dummy(ImVec2((modalSize.x), 10));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Log In with GitHub",buttonSize))
                    {
                        puts("GitHub");
                        this->openAuthProvider("github");
                    }

                    ImGui::Dummy(ImVec2((modalSize.x), 10));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Log In with Google",buttonSize))
                    {
                        puts("Google");
                        this->openAuthProvider("google");
                    }

                    ImGui::Dummy(ImVec2((modalSize.x), 10));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Log In with Twitter",buttonSize))
                    {
                        puts("Twitter");
                        this->openAuthProvider("twitter");
                    }

                    ImGui::Dummy(ImVec2((modalSize.x), 10));
                    ImGui::SetCursorPosX((modalSize.x / 2) - (buttonSize.x / 2));
                    if (ImGui::Button("Continue Anonymous",buttonSize))
                    {
                        LoginView::Cancel();
                    }

                }
            }
            ImGui::End();
        }
    }
}

void LoginView::Cancel() {
    getContext()->_sentAuthentication = false;
    getContext()->_startingAuthentication = false;
}

int LoginView::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void LoginView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void LoginView::openAuthProvider(const std::string& provider) {
    getContext()->_sentAuthentication = true;
    UserService userService = UserService();
    userService.openAuth(provider);

    std::thread thrContext(LoginView::createServer, getContext());
    thrContext.detach();
}

void LoginView::createServer(Context* context) {
    HttpServer server(context, 9494);
    server.Run();
}
