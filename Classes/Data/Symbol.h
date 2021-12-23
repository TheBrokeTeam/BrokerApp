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

    const std::string& getName() const{
        return _name;
    }

    void setName(const std::string& symbol){
        _name = symbol;
    }

    long getTimeIntervalInMinutes() const{
        return getMinutesFromTimeInterval(_interval);
    }

    Interval getTimeInterval() const{
        return _interval;
    }

    void setTimeInterval(Interval timeInterval){
        _interval = timeInterval;
    }

    static int getMinutesFromTimeInterval(Interval interval) {
        std::vector<int> intArr = {1,3,5,15,39,60,60*2,60*4,60*6,60*8,60*12,60*24,60*24*3,60*24*7,60*24*30};
        return intArr[int(interval)];
    }

private:
    std::string _name{""};
    Interval _interval;
    TimeRange _range{0,0};
};


#endif //BROKERAPP_SYMBOL_H
