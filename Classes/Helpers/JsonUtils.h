//
// Created by Maykon Meneghel on 12/01/22.
//

#ifndef BROKERAPP_JSONUTILS_H
#define BROKERAPP_JSONUTILS_H

#include <string>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

namespace json {
    static std::string Stringfy(const rapidjson::Document &document) {
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        document.Accept(writer);
        return strbuf.GetString();
    }

    static rapidjson::Document Parse(const std::string& s) {
        rapidjson::Document d(rapidjson::kObjectType);
        rapidjson::Value data(rapidjson::kObjectType);
        rapidjson::Value value;
        value.SetString(s.c_str(), d.GetAllocator());
        data.AddMember("value", value, d.GetAllocator());
        d.AddMember("data", data, d.GetAllocator());
        return d;
    }

}

#endif //BROKERAPP_JSONUTILS_H
