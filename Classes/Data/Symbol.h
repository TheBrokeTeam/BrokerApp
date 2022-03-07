//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_SYMBOL_H
#define BROKERAPP_SYMBOL_H

#include "BarData.h"
#include <rapidcsv.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include "TickData.h"
#include <string>
#include <vector>
#include <imgui.h>

class Symbol {
public:

//    Symbol() = default;
    explicit Symbol(std::string code) : _code(std::move(code)) { _interval = Interval::Interval_Unknown; _range = TimeRange();}
    explicit Symbol(const std::string& code, const std::string& interval, long startTime, long endTime);

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

    struct Path {
        std::string dirname;
        std::string zip_filename;
        std::string csv_filename;
    };

    const std::string& getCode() const;
    [[nodiscard]] long getStartTime() const;
    [[nodiscard]] long getEndTime() const;
    [[nodiscard]] std::string getStartDate() const;
    [[nodiscard]] std::string getEndDate() const;

    long getTimeIntervalInMinutes();

    //used in live context
    long getTimeIntervalInSeconds();
    double getTimeIntervalInMiliSeconds();

    bool operator < (const Symbol& rhs) const {return _interval<rhs._interval;}

    std::vector<TickData> fetchData();
    std::vector<TickData> fetchCSVData();
    std::vector<TickData> loadJson(const rapidjson::Document&);
    std::vector<TickData> loadCSV(Path);

//    bool dataAlreadyExists(const std::string&);

private:
    std::string _code;
    Interval _interval;
    TimeRange _range{0,0};

    static Interval stringToInterval(const std::string&);
    std::string intervalToString();
    long getStepHourFromInterval();
    static std::string timestampToStringDate(long ms);
    static long getNextTimestampMonth(long);
    std::string getSymbolFilePath(const std::string&, const std::string&);
    static void sleeping(const int&);
};

#endif //BROKERAPP_SYMBOL_H
