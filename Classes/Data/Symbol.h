//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_SYMBOL_H
#define BROKERAPP_SYMBOL_H

#include "BarData.h"
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "TickData.h"
#include <string>
#include <vector>
#include <imgui.h>

class Symbol {
public:

    // temp vars for download purposes
    std::string month{"01"};
    std::string year{"2021"};

    enum class Interval {
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
        Interval_1Month,
        Interval_Unknown
    };

    struct TimeRange {
        long start;
        long end;
    };

    inline const char * ToString(Interval v) const {
        switch (v) {
            case Interval::Interval_1Minute: return "1m";
            case Interval::Interval_3Minutes: return "3m";
            case Interval::Interval_5Minutes: return "5m";
            case Interval::Interval_15Minutes: return "15m";
            case Interval::Interval_30Minutes: return "30m";
            case Interval::Interval_1Hour: return "1h";
            case Interval::Interval_2Hour: return "2h";
            case Interval::Interval_4Hour: return "4h";
            case Interval::Interval_6Hour: return "6h";
            case Interval::Interval_8Hour: return "8h";
            case Interval::Interval_12Hour: return "12h";
            case Interval::Interval_1Day: return "1d";
            case Interval::Interval_3Days: return "3d";
            case Interval::Interval_1Week: return "1w";
            case Interval::Interval_1Month: return "1M";
            default:      return "[Unknown Interval]";
        }
    }

    void setName(const std::string&);
    void setTimeInterval(Interval);
    const std::string& getName();
    std::string getInterval();
    long getStartTime();
    long getEndTime();
    long getTimeIntervalInMinutes();
    static int getMinutesFromTimeInterval(Interval interval);

    Symbol() = default;
    explicit Symbol(std::string code) : _code(std::move(code)) {}
    explicit Symbol(const std::string& code, const std::string& interval, long startTime, long endTime);

    bool operator < (const Symbol& rhs) const {return _interval<rhs._interval;}

    std::vector<TickData> fetchData();

    std::vector<TickData> loadJson(const rapidjson::Document& json);

private:
    std::string _code;
    Interval _interval;
    TimeRange _range{0,0};

    Interval resolveInterval(const std::string&);

    long getStepHourFromInterval();

    static void sleeping(const int&);
};



#endif //BROKERAPP_SYMBOL_H
