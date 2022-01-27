//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIROUTER_H
#define UNTITLED1_APIROUTER_H

#include <string>
#include <map>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

enum RequestMethod {
    get,
    post,
    patch,
    del
};

class APIRouter {
private:
    RequestMethod method;
    std::string path;
    std::string body;
protected:
    rapidjson::Document get(const std::string& endpoint);
    rapidjson::Document post(const std::string& endpoint);
    rapidjson::Document patch(const std::string& endpoint);
    rapidjson::Document del(const std::string& endpoint);
public:
    APIRouter(RequestMethod method, std::string path);
    RequestMethod getMethod();
    std::string getPath();
    std::string getBody();
    void setBody(std::string newBody);
    rapidjson::Document request(const std::string& endpoint);
};

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string* data);

#endif //UNTITLED1_APIROUTER_H