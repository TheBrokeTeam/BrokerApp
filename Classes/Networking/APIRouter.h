//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIROUTER_H
#define UNTITLED1_APIROUTER_H

#include <string>
#include <map>
#include <json/json.h>

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
    Json::Value body;
protected:
    Json::Value get(const std::string& endpoint);
    Json::Value post(const std::string& endpoint);
    Json::Value patch(const std::string& endpoint);
    Json::Value del(const std::string& endpoint);
public:
    APIRouter(RequestMethod method, std::string path);
    RequestMethod getMethod();
    std::string getPath();
    Json::Value getBody();
    void setBody(Json::Value newBody);
    Json::Value request(const std::string& endpoint);
};

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string* data);

static Json::Value JsonDecode(const std::string& text);

#endif //UNTITLED1_APIROUTER_H
