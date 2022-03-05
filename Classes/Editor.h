//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_EDITOR_H
#define BROKERAPP_EDITOR_H

#include "App.h"
#include <vector>
#include "Contexts/Context.h"
#include "Helpers/Utils.h"

class Ticker;
class Editor : public App {
public:

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
        node_trade_black
    };

    ImageInfo getTexture(Icons icon);
    std::map<Icons,ImageInfo> _imagesRef;

    using App::App;
    virtual ~Editor();
    void start() override;
    void update() override;

    void showDockSpace();
private:
    //delta time helpers
    float _lastTime = 0;
    float getDeltaTime();

    void loadImage(Icons icon,const std::string& filepath);
    std::shared_ptr<Context> _context{nullptr};

};


#endif //BROKERAPP_EDITOR_H
