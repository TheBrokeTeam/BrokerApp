//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_EDITOR_H
#define BROKERAPP_EDITOR_H

#include "App.h"
#include <vector>
#include "Widgets/Widget.h"
#include "Contexts/Context.h"

class Ticker;
class Editor : public App {
public:
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
    void showCharts(bool show);

private:

    std::vector<std::shared_ptr<Widget>> _widgets;
    void BeginWindow();
    bool _editor_begun = false;
    std::shared_ptr<Context> _context{nullptr};

    //delta time helpers
    float _lastTime = 0;
    float getDeltaTime();
};


#endif //BROKERAPP_EDITOR_H
