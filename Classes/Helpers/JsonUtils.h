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

}

#endif //BROKERAPP_JSONUTILS_H
