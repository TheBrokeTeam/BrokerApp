//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#ifndef BROKERAPP_DOWNLOADERVIEW_H
#define BROKERAPP_DOWNLOADERVIEW_H


#include "Widget.h"

class DownloaderView : public Widget
{
public:
    DownloaderView(Context* context);

    struct FetchInfo{
        std::string fetchInterVal{"1m"};
        std::string fetchYear{"2022"};
        std::string fetchMonth{"01"};
        std::string fetchSymbol{"ETHUSDT"};
    };

    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

private:
    FetchInfo _info;
};

#endif //BROKERAPP_DOWNLOADERVIEW_H
