//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_EDITOR_H
#define BROKERAPP_EDITOR_H

#include "App.h"
#include <vector>
#include "Widgets/Widget.h"
#include "Contexts/Context.h"
#include "Helpers/Utils.h"
#include "Tickables/Strategies/TestStrategy.h"

class Ticker;
class Editor : public App {
public:

    inline static const ImVec4 broker_yellow = ImVec4(255.0f/255, 191.0f/255,64.0f/255, 1.00f);
    inline static const ImVec4 broker_yellow_active = ImVec4(153.0f/255, 102.0f/255,0.0f/255, 1.00f);
    inline static const ImVec4 broker_yellow_hover = ImVec4(255.0f/255, 238.0f/255,204.0f/255, 1.00f);
    inline static const ImVec4 broker_white = ImVec4(220.0f/255, 220.0f/255,220.0f/255, 1.00f);
    inline static const ImVec4 broker_dark_grey = ImVec4(24.0f/255, 26.0f/255,31.0f/255, 1.00f);
    inline static const ImVec4 broker_light_grey = ImVec4(62.0f/255, 62.0f/255,62.0f/255, 1.00f);
    inline static const ImVec4 broker_clear = ImVec4(0, 0,0, 0.00f);

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
        trash
    };


    ImageInfo getTexture(Icons icon);


    std::map<Icons,ImageInfo> _imagesRef;

    using App::App;
    virtual ~Editor();
    void start() override;
    void update() override;

    template<typename T>
    T* getWidget()
    {
        for (const auto& widget : _widgets)
        {
            if (T* widget_t = dynamic_cast<T*>(widget.get()))
            {
                return widget_t;
            }
        }

        return nullptr;
    }

    Context* getContext();

    void addChartWidget(Ticker* ticker);
    void showDataLoader(bool show);
    void showSimulationController(bool show);

    void showCharts(bool show);
    void showIndicators(bool show);
    void showTabBars(bool show);

    void showDockSpace();

    void setStrategyTest(TestStrategy* strategy);


private:
    std::vector<std::shared_ptr<Widget>> _widgets;
    std::shared_ptr<Context> _context{nullptr};

    //delta time helpers
    float _lastTime = 0;
    float getDeltaTime();

    void loadImage(Icons icon,const std::string& filepath);
    TestStrategy* _strategy{nullptr};

};


#endif //BROKERAPP_EDITOR_H
