//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_EDITOR_H
#define BROKERAPP_EDITOR_H

#include <App.h>

class Editor : public App {
public:
    using App::App;
    ~Editor();
    void start() override;
    void update() override;

private:
//    //event bus
//    std::unique_ptr<Listener> _listener{nullptr};
//    std::shared_ptr<EventBus> _bus = std::make_shared<EventBus>();
//
//    //managers
//    std::unique_ptr<UIManager> _uiManager{nullptr};
//    std::unique_ptr<DataManager> _dataManager{nullptr};
//
//    //Actions of application as bridge functions
//    void fetchData(const ui_event::FetchButtonClicked &event);


    //delta time helpers
    float _lastTime = 0;
    float getDeltaTime();

};


#endif //BROKERAPP_EDITOR_H
