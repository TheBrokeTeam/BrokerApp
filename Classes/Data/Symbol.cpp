//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Symbol.h"
#include "../Networking/Services/KLineService.h"


Symbol::Symbol(const std::string &code, const std::string &interval, long startTime, long endTime) {
    _code = code;
    _interval = resolveInterval(interval);
    _range = {startTime,endTime};
}


Symbol::Interval Symbol::resolveInterval(const std::string& value) {
    if ( value == "1m" ) return Interval::Interval_1Minute;
    if ( value == "3m" ) return Interval::Interval_3Minutes;
    if ( value == "5m" ) return Interval::Interval_5Minutes;
    if ( value == "15m" ) return Interval::Interval_15Minutes;
    if ( value == "30m" ) return Interval::Interval_30Minutes;
    if ( value == "1h" ) return Interval::Interval_1Hour;
    if ( value == "2h" ) return Interval::Interval_2Hour;
    if ( value == "4h" ) return Interval::Interval_4Hour;
    if ( value == "6h" ) return Interval::Interval_6Hour;
    if ( value == "8h" ) return Interval::Interval_8Hour;
    if ( value == "12h" ) return Interval::Interval_12Hour;
    if ( value == "1d" ) return Interval::Interval_1Day;
    if ( value == "3d" ) return Interval::Interval_3Days;
    if ( value == "1w" ) return Interval::Interval_1Week;
    if ( value == "1mo" ) return Interval::Interval_1Month;
}

rapidjson::Document Symbol::fetchData() {
    KLineService service;
    return service.fetchData(*this);
}

void Symbol::setName(const std::string& symbol){
    _code = symbol;
}

void Symbol::setTimeInterval(Interval timeInterval){
    _interval = timeInterval;
}

const std::string& Symbol::getName(){
    return _code;
}

std::string Symbol::getInterval() {
    return ToString(_interval);
}

long Symbol::getTimeIntervalInMinutes() {
    return getMinutesFromTimeInterval(_interval);
}

int Symbol::getMinutesFromTimeInterval(Interval interval) {
    std::vector<int> intArr = {1,3,5,15,39,60,60*2,60*4,60*6,60*8,60*12,60*24,60*24*3,60*24*7,60*24*30};
    return intArr[int(interval)];
}

long Symbol::getStartTime() {
    return _range.start;
}

long Symbol::getEndTime() {
    return _range.end;
}