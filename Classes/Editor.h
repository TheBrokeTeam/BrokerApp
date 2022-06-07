//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_EDITOR_H
#define BROKERAPP_EDITOR_H

#include "App.h"
#include <vector>
#include "Contexts/Context.h"
#include "Helpers/Utils.h"
#include "Networking/Binance/SocketManager.h"
#include "Networking/Binance/RestApiManager.h"

class Ticker;
class Editor : public App {
public:
    enum class ContextType{
        None,
        BackTesting,
        LiveTrade
    };

    inline static bool showAboutWindow         = false;
    inline static bool show_tabbars         = false;
    inline static bool imgui_metrics         = false;
    inline static bool imgui_style           = false;
    inline static bool imgui_demo            = false;
    inline static bool implot_demo            = false;

    inline static const ImVec4 broker_yellow = ImVec4(255.0f/255, 191.0f/255,64.0f/255, 1.00f);
    inline static const ImVec4 broker_yellow_active = ImVec4(153.0f/255, 102.0f/255,0.0f/255, 1.00f);
    inline static const ImVec4 broker_yellow_hover = ImVec4(255.0f/255, 238.0f/255,204.0f/255, 1.00f);
    inline static const ImVec4 broker_white = ImVec4(220.0f/255, 220.0f/255,220.0f/255, 1.00f);
    inline static const ImVec4 broker_green = ImVec4(0.52f, 0.6f,0.0f, 1.00f);
    inline static const ImVec4 broker_red = ImVec4(1.0f, 0.5f,0.35f, 1.00f);
    inline static const ImVec4 broker_dark_grey = ImVec4(24.0f/255, 26.0f/255,31.0f/255, 1.00f);
    inline static const ImVec4 broker_light_grey = ImVec4(62.0f/255, 62.0f/255,62.0f/255, 1.00f);
    inline static const ImVec4 broker_clear = ImVec4(0, 0,0, 0.00f);

    inline static const ImVec4 broker_pnl_profit = ImVec4(0.3f, 0.3f,1.0f, 0.3f);
    inline static const ImVec4 broker_pnl_loss = ImVec4(1.0f, 0.3f,0.3f, 0.3f);
    inline static const ImVec4 broker_pnl_profit_line = ImVec4(0.3f, 0.3f,1.0f, 1.0f);
    inline static const ImVec4 broker_pnl_loss_line = ImVec4(1.0f, 0.3f,0.3f, 1.0f);



    inline static const ImVec4 broker_black = ImVec4(0.0f, 0.0f,0.0f, 1.00f);

    struct ImageInfo {
        int my_image_width = 0;
        int my_image_height = 0;
        GLuint my_image_texture = 0;
    };

    enum class Icons{
        none,
        indicator_ma,
        close_window,
        trash,
        node_cross,
        node_counter,
        node_bar_seq_down,
        node_bar_seq_up,
        node_trend,
        node_trade,
        node_cross_black,
        node_counter_black,
        node_bar_seq_down_black,
        node_bar_seq_up_black,
        node_trend_black,
        node_trade_black,
        fav_selected,
        fav_unselected,
        garbage_bin
    };

    ImageInfo getTexture(Icons icon);
    std::map<Icons,ImageInfo> _imagesRef;

    using App::App;
    virtual ~Editor();
    void start() override;
    void update() override;
    void showDockSpace();

    const Editor::ContextType& getContextType();
    void loadContext(ContextType type);

    SocketManager* getSocketManager(){
        return _socketManager.get();
    }

    RestApiManager* getApiManager(){
        return _apiManager.get();
    }

private:
    void internalLoadContext();
    bool shouldReloadContext = false;
    ContextType _nextContextType;

    ContextType _contextType;
    //delta time helpers
    float _lastTime = 0;
    float getDeltaTime();

    void loadImage(Icons icon,const std::string& filepath);
    std::unique_ptr<Context> _context{nullptr};
    std::unique_ptr<SocketManager> _socketManager{nullptr};
    std::unique_ptr<RestApiManager> _apiManager{nullptr};

};


#endif //BROKERAPP_EDITOR_H
