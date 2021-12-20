//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_SYMBOL_H
#define BROKERAPP_SYMBOL_H

#include "BarData.h"
#include <string>
#include <vector>
#include <imgui.h>

class Symbol {
public:
    enum class Interval
    {
        Interval_1Minute,
        Interval_3Minutes,
        Interval_5Minutes,
        Interval_15Minutes,
        Interval_30Minutes,
        Interval_1Hour,
        Interval_2Hour,
        Interval_4Hour,
        Interval_6Hour,
        Interval_8Hour,
        Interval_12Hour,
        Interval_1Day,
        Interval_3Days,
        Interval_1Week,
        Interval_1Month
    };
    struct TimeRange{
        double start;
        double end;
    };

    Symbol() = default;
    explicit Symbol(std::string name) : _name(std::move(name)) {}

    const std::string& getName(){
        return _name;
    }

    void setName(const std::string& symbol){
        _name = symbol;
    }

    long getTimeIntervalInMinutes(){
        return _timeIntervalInMinutes;
    }

    void setTimeInterval(Interval timeInterval){
        _interval = timeInterval;
    }

private:
    std::string _name{""};
    long _timeIntervalInMinutes{0};
    Interval _interval;
    TimeRange _range{0,0};
};


#endif //BROKERAPP_SYMBOL_H
