//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#ifndef BROKERAPP_DATALOADER_H
#define BROKERAPP_DATALOADER_H


#include "Widget.h"

class DataLoader : public Widget
{
public:
    DataLoader(Context* context);

    struct FetchInfo{
        std::string fetchInterVal{"15m"};
        std::string fetchYear{"2021"};
        std::string fetchMonth{"01"};
        std::string fetchSymbol{"ETHUSDT"};
    };

    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

private:
    FetchInfo _info;
};

#endif //BROKERAPP_DATALOADER_H
