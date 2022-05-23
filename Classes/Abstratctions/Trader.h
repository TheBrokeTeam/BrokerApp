//
// Created by Arthur Abel Motelevicz on 30/03/22.
//

#ifndef BROKERAPP_TRADER_H
#define BROKERAPP_TRADER_H

class Context;

class Trader {
public:
    Trader(Context*);
    ~Trader();
    void requestOpenPosition();
    void requestClosePosition();
    void openPosition();
    void closePosition();
private:
};


#endif //BROKERAPP_TRADER_H
