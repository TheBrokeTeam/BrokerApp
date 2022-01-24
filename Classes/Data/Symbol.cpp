//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Symbol.h"
#include "../Networking/Services/KLineService.h"
#include <iostream>
#include "../Helpers/JsonUtils.h"
#include <chrono>
#include <thread>

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

std::vector<TickData> Symbol::fetchData() {
    long currentTime = this->getStartTime();
    long endTime = this->getEndTime();

    KLineService service;

    std::vector<TickData> data;

    while (currentTime < endTime){
        long newEndTime = currentTime + 12 * 60 * 60 * 1000;

        rapidjson::Document jsonData = service.fetchData(this->getName(), this->getInterval(), currentTime, newEndTime, 1000);

        std::vector<TickData> d = loadJson(jsonData);
        data.insert(std::end(data), std::begin(d), std::end(d));
        currentTime = newEndTime;

        // sleeping
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return data;
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

std::vector<TickData> Symbol::loadJson(const rapidjson::Document& json) {
    std::vector<TickData> output;

    for(rapidjson::SizeType i = 0; i < json.Size(); i++){
        const rapidjson::Value &data_vec = json[i];

        TickData data_open;
        TickData data_high;
        TickData data_low;
        TickData data_close;

        //converting ms to sec and add simulated time for the sub tick on the bars
        double timeInSec = data_vec[rapidjson::SizeType(0)].GetDouble() / 1000.0;
        data_open.time = timeInSec;
        data_high.time = timeInSec + this->getTimeIntervalInMinutes() * 0.25 * 60;
        data_low.time = timeInSec + this->getTimeIntervalInMinutes() * 0.5 * 60;
        data_close.time = timeInSec + this->getTimeIntervalInMinutes() * 60 - 1;

        data_open.price = std::atof(data_vec[rapidjson::SizeType(1)].GetString());
        data_high.price = std::atof(data_vec[rapidjson::SizeType(2)].GetString());
        data_low.price = std::atof(data_vec[rapidjson::SizeType(3)].GetString());
        data_close.price = std::atof(data_vec[rapidjson::SizeType(4)].GetString());

        //0.25 volume for each tick
        double volume = std::atof(data_vec[rapidjson::SizeType(5)].GetString()) * 0.25;

        data_open.volume = volume;
        data_high.volume = volume;
        data_low.volume = volume;
        data_close.volume = volume;

        output.push_back(data_open);
        output.push_back(data_high);
        output.push_back(data_low);
        output.push_back(data_close);

    }

    return output;
}