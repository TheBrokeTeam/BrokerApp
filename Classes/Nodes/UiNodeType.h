//
// Created by Luiz Veloso on 23/01/22.
//

#ifndef BROKERAPP_UINODETYPE_H
#define BROKERAPP_UINODETYPE_H

//all types of possible nodes rendered on editor (indicators + other nodes)
enum class UiNodeType
{
    SMA,
    EMA,
    WMA,
    TRIX,
    PSAR,
    BOLL,
    VWAP,
    CROSS,
    COUNTER,
    BAR_SEQ_DOWN,
    BAR_SEQ_UP,
    TREND,
    SOURCE,
    TRADE
};


#endif //BROKERAPP_UINODETYPE_H
