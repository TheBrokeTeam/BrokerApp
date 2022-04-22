//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#ifndef BROKERAPP_ACCOUNTINFO_H
#define BROKERAPP_ACCOUNTINFO_H

#include <string>
#include <binapi/api.hpp>

struct AccountInfo{
    std::string userId{""};
    std::string token{""};
    double makerCommission = 0;
    double takerCommission = 0;
    double buyerCommission = 0;
    double sellerCommission = 0;
    bool canTrade = false;
    bool canWithdraw = false;
    bool canDeposit = false;
    double updateTime = 0;
    struct balance {
        std::string asset{""};
        double free = 0;
        double locked = 0;
    };
    std::vector<balance> balances;

    void update(const AccountInfo& newInfo){
        this->makerCommission =     newInfo.makerCommission;
        this->takerCommission =     newInfo.takerCommission;
        this->buyerCommission =     newInfo.buyerCommission;
        this->sellerCommission =    newInfo.sellerCommission;
        this->canTrade =            newInfo.canTrade;
        this->canWithdraw =         newInfo.canWithdraw;
        this->canDeposit =          newInfo.canDeposit;
        this->updateTime =          newInfo.updateTime;

        this->balances.clear();
        balances = newInfo.balances;
    }
};

#endif //BROKERAPP_ACCOUNTINFO_H
