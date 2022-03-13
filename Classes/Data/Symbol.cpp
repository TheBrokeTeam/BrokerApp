//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Symbol.h"
#include "../Networking/Services/KLineService.h"
#include <iostream>
#include <fmt/format.h>
#include "../Helpers/JsonUtils.h"
#include <chrono>
#include <thread>

Symbol::Symbol(const std::string &code, const std::string &interval, long startTime, long endTime) {
    _code = code;
    _interval = stringToInterval(interval);
    _range = {startTime,endTime};
}

Symbol::Interval Symbol::stringToInterval(const std::string& value) {
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
    else return Interval::Interval_Unknown;
}

std::string Symbol::intervalToString() {
    switch (_interval) {
        case Interval::Interval_1Minute:    return "1m";
        case Interval::Interval_3Minutes:   return "3m";
        case Interval::Interval_5Minutes:   return "5m";
        case Interval::Interval_15Minutes:  return "15m";
        case Interval::Interval_30Minutes:  return "30m";
        case Interval::Interval_1Hour:      return "1h";
        case Interval::Interval_2Hour:      return "2h";
        case Interval::Interval_4Hour:      return "4h";
        case Interval::Interval_6Hour:      return "6h";
        case Interval::Interval_8Hour:      return "8h";
        case Interval::Interval_12Hour:     return "12h";
        case Interval::Interval_1Day:       return "1d";
        case Interval::Interval_3Days:      return "3d";
        case Interval::Interval_1Week:      return "1w";
        case Interval::Interval_1Month:     return "1M";
        default:                            return "[Unknown Interval]";
    }
}

long Symbol::getStepHourFromInterval() {
    switch (_interval) {
        case Interval::Interval_1Minute:    return 16;
        case Interval::Interval_3Minutes:   return 50;
        case Interval::Interval_5Minutes:   return 83;
        case Interval::Interval_15Minutes:  return 250;
        case Interval::Interval_30Minutes:  return 500;
        case Interval::Interval_1Hour:      return 1000;
        case Interval::Interval_2Hour:      return 2000;
        case Interval::Interval_4Hour:      return 4000;
        case Interval::Interval_6Hour:      return 6000;
        case Interval::Interval_8Hour:      return 8000;
        case Interval::Interval_12Hour:     return 12000;
        case Interval::Interval_1Day:       return 24000;
        case Interval::Interval_3Days:      return 72000;
        case Interval::Interval_1Week:      return 168000;
        case Interval::Interval_1Month:     return 720000;
        default:                            return 16;
    }
}

const std::string& Symbol::getCode() const{
    return _code;
}

long Symbol::getTimeIntervalInMinutes() {
    std::vector<int> intArr = {1,3,5,15,30,60,60*2,60*4,60*6,60*8,60*12,60*24,60*24*3,60*24*7,60*24*30};
    return intArr[int(_interval)];
}

long Symbol::getStartTime() const {
    return _range.start;
}

long Symbol::getEndTime() const {
    return _range.end;
}

std::string Symbol::getStartDate() const {
    return timestampToStringDate(_range.start);
}

std::string Symbol::getEndDate() const {
    return timestampToStringDate(_range.end);
}

std::string Symbol::timestampToStringDate(long ms) {
    long inSecs = ms / 1000;
    auto tm = *std::localtime(&inSecs);
    long year = tm.tm_year + 1900;
    long month = tm.tm_mon + 1;
    return fmt::format("{:04}-{:02}", year, month);
}

void Symbol::sleeping(const int & ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
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
        double timeInSec = data_vec[rapidjson::SizeType(0)].GetDouble();
        data_open.time = timeInSec;
        data_high.time  = timeInSec + 20000;//simulate 20 sec after
        data_low.time  = timeInSec + 40000;//simulate 40 sec after
        data_close.time  = timeInSec + this->getTimeIntervalInMiliSeconds();//simulate 60 sec before

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

std::vector<TickData> Symbol::loadCSV(Path filepath){

    std::vector<TickData> output;

    try {
        rapidcsv::Document doc(filepath.csv_filename, rapidcsv::LabelParams(-1, -1));

        for(int i = 0; i < doc.GetRowCount(); i++)
        {
            TickData data_open;
            TickData data_high;
            TickData data_low;
            TickData data_close;

            //converting ms to sec and add simulated time for the sub tick on the bars
            double timeInSec = doc.GetCell<double>(0,i);
            data_open.time   = timeInSec;
            data_high.time   = timeInSec + 20000;//simulate 20 sec after
            data_low.time    = timeInSec + 40000;//simulate 40 sec after
            data_close.time  = timeInSec + this->getTimeIntervalInMiliSeconds();//simulate 60 sec before

            data_open.price = doc.GetCell<double>(1,i);
            data_high.price = doc.GetCell<double>(2,i);
            data_low.price = doc.GetCell<double>(3,i);
            data_close.price = doc.GetCell<double>(4,i);

            //0.25 volume for each tick
            double volume = doc.GetCell<double>(5,i)*0.25;
            data_open.volume = volume;
            data_high.volume = volume;
            data_low.volume = volume;
            data_close.volume = volume;

            output.push_back(data_open);
            output.push_back(data_high);
            output.push_back(data_low);
            output.push_back(data_close);
        }

    } catch(std::exception exception) {
        std::cout << "Problema em carregar o CSV" << std::endl;
    }
    return output;
}

std::string Symbol::getSymbolFilePath(const std::string& date, const std::string& extension) {

    std::string out = fmt::format("./Data/{}/{}-{}-{}.{}",
                                  getCode(),
                                  getCode(),
                                  (intervalToString() == "1M") ? "1mo" : intervalToString(),
                                  date,
                                  extension);

    return out;
}

std::vector<TickData> Symbol::fetchData() {
    long currentTime = this->getStartTime();
    long endTime = this->getEndTime();

    KLineService service;

    std::vector<TickData> data;

    int i = 0;
    while (currentTime < endTime){
        std::thread t1(sleeping, 50);

        long newEndTime = currentTime + (getStepHourFromInterval() * (60 * 60 * 1000));

        rapidjson::Document jsonData = service.fetchData(getCode(), intervalToString(), currentTime, newEndTime - (60 * 1000), 1000);

        std::vector<TickData> d = loadJson(jsonData);

        data.insert(std::end(data), std::begin(d), std::end(d));
        currentTime = newEndTime;

        t1.join();
    }

    return data;
}

std::vector<TickData> Symbol::fetchCSVData() {
    long currentTime = this->getStartTime();
    long endTime = this->getEndTime();

    if(!std::filesystem::exists("./Data"))
        std::filesystem::create_directory("./Data");

    if(!std::filesystem::exists(fmt::format("./Data/{}", getCode())))
        std::filesystem::create_directory(fmt::format("./Data/{}", getCode()));

    KLineService service;
    std::vector<TickData> data;

    while(currentTime < endTime) {
        std::string date = timestampToStringDate(currentTime);

        Path filepath = Path{fmt::format("./Data/{}", getCode()),
                             getSymbolFilePath(date, "zip"),
                             getSymbolFilePath(date, "csv")};

        if(!std::filesystem::exists(filepath.csv_filename))
            service.downloadData(getCode(),
                                 (intervalToString() == "1M") ? "1mo" : intervalToString(),
                                 date,
                                 filepath);

        std::vector<TickData> d = loadCSV(filepath);

        if(!d.empty())
            data.insert(std::end(data), std::begin(d), std::end(d));

        currentTime = Symbol::getNextTimestampMonth(currentTime);
    }

    std::vector<TickData> matched;
    for (TickData &ref: data)
        if (ref.time >= (getStartTime()) && ref.time <= (getEndTime()))
            matched.push_back(ref);

    std::cout << "Data: " << data.size() << " values." << std::endl;
    std::cout << "Matched: " << matched.size() << " values." << std::endl;

    return matched;
}

//bool Symbol::dataAlreadyExists(const std::string& date) {
//    return std::filesystem::exists(getSymbolFilePath(date, "csv"));
//}

long Symbol::getNextTimestampMonth(long ts) {
    long inSecs = ts / 1000;
    std::tm* now = std::localtime(&inSecs);
    now->tm_mon += 1;
    return timelocal(now) * 1000;;
}

long Symbol::getTimeIntervalInSeconds() {
    std::vector<long> intArr = {
              60,
              60*3,
              60*5,
              60*15,
              60*30,
              60*60,
              60*60*2,
              60*60*4,
              60*60*6,
              60*60*8,
              60*60*12,
              60*60*24,
              60*60*24*3,
              60*60*24*7,
              60*60*24*30
    };
    return intArr[int(_interval)];
}
double Symbol::getTimeIntervalInMiliSeconds() {
    std::vector<long> intArr = {
            1000*60*1,
            1000*60*3,
            1000*60*5,
            1000*60*15,
            1000*60*30,
            1000*60*60,
            1000*60*60*2,
            1000*60*60*4,
            1000*60*60*6,
            1000*60*60*8,
            1000*60*60*12,
            1000*60*60*24,
            1000*60*60*24*3,
            1000*60*60*24*7,
            1000*60*60*24*30
    };
    return intArr[int(_interval)];
}
