//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#ifndef BROKERAPP_BASTRING_H
#define BROKERAPP_BASTRING_H


#include <iostream>

class BAString
{
public:

    static std::string uuid();

    static bool startsWith(const std::string& str, const std::string& start);
    static bool endsWith(const std::string& str, const std::string& end);

    static std::string uppercased(const std::string& str);
    static std::string lowercased(const std::string& str);

    static bool queryMatches(const std::string& query, const std::string& text);
    static std::string normalizeForQuery(const std::string& query);

    static std::string captureStringArguments(const std::string input, const char* arg...);
    static std::string captureStringArguments(const std::string input, const std::vector<std::string> &args);

    static void replace(std::string& string, const std::string& occurrence, const std::string& replacement);
    static std::string replacing(const std::string& string, const std::string& occurrence, const std::string& replacement);

    static void trim(std::string& string, const std::string& characters = " ");
    static std::string trimmed(const std::string& string, const std::string& characters = " ");

    static bool isNumber(const std::string& str);
    static bool isInteger(const std::string& str);

    static int getInt(const std::string& str);
    static float getFloat(const std::string& str);

    static bool contains(const std::string& str, const std::string& subStr);

    static std::string toString(const void*);

    static std::vector<std::string> split(const std::string& str, char delimiter);
};


#endif //BROKERAPP_BASTRING_H
