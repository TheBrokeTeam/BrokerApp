//
// Created by Luiz Veloso on 23/01/22.
//

#ifndef BROKERAPP_NODETYPE_H
#define BROKERAPP_NODETYPE_H

//Internal Nodes inside th graph
enum class NodeType
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
    TRADE,
    SOURCE,
    VALUE
};


#endif //BROKERAPP_NODETYPE_H
