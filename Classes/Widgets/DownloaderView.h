//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#ifndef BROKERAPP_DOWNLOADERVIEW_H
#define BROKERAPP_DOWNLOADERVIEW_H


#include "Widget.h"
#include <thread>

class DownloaderView : public Widget
{
public:
    DownloaderView(Context* context);

    struct FetchInfo{
        std::string fetchInterVal{"1m"};
        std::string fetchSymbol{"ETHUSDT"};
        long fetchStartTime{};
        long fetchEndTime{};
    };

    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
    static void fetchingSymbol(const FetchInfo&, Context*);

private:
    FetchInfo _info;
    tm startDate{};
    tm endDate{};
    bool showWarning=false;
};

#endif //BROKERAPP_DOWNLOADERVIEW_H
