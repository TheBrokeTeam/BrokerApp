//
// Created by Maykon Meneghel on 07/01/22.
//

#include "APIRouter.h"
#include <utility>
#include "curl//curl.h"
#include "curl/easy.h"
#include <json/json.h>
#include <iostream>

APIRouter::APIRouter(RequestMethod method, std::string path) {
    this->method = method;
    this->path = std::move(path);
    this->body = {{"",""}};
}

std::string APIRouter::getPath() {
    return this->path;
}

RequestMethod APIRouter::getMethod() {
    return this->method;
}

Json::Value APIRouter::getBody() {
    return this->body;
}

void APIRouter::setBody(Json::Value newBody) {
    this->body = std::move(newBody);
}

Json::Value APIRouter::get(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    std::cout << endpoint << std::endl;
    CURL *curl;
    CURLcode error;

    std::string readBuffer;
    std::string readHeader;
    long response_code;
    double elapsed;
    char* effective_url;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());

        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
//        curl_easy_setopt(curl, CURLOPT_USERPWD, "user:pass");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &readHeader);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective_url);

        error = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        if(error != 0) {
            Json::Value errorMessage;
            errorMessage["code"] = std::to_string(response_code);
            errorMessage["message"] = readBuffer;
            return errorMessage;
        }
        return JsonDecode(readBuffer);
    }
    return JsonDecode("");
}

Json::Value APIRouter::post(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    std::string readBuffer;
    std::string readHeader;
    long response_code;
    double elapsed;
    char* effective_url;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());

        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        std::string bodyString = this->getBody().toStyledString();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyString.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, bodyString.length());
        curl_easy_setopt(curl, CURLOPT_POST, 1);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &readHeader);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective_url);

        error = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        if(error != 0) {
            Json::Value errorMessage;
            errorMessage["code"] = std::to_string(response_code);
            errorMessage["message"] = readBuffer;
            return errorMessage;
        }
        return JsonDecode(readBuffer);
    }
    return JsonDecode("");
}

Json::Value APIRouter::patch(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    std::string readBuffer;
    std::string readHeader;
    long response_code;
    double elapsed;
    char* effective_url;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());

        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &readHeader);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective_url);

        error = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        if(error != 0) {
            Json::Value errorMessage;
            errorMessage["code"] = std::to_string(response_code);
            errorMessage["message"] = readBuffer;
            return errorMessage;
        }
        return JsonDecode(readBuffer);
    }
    return JsonDecode("");
}

Json::Value APIRouter::del(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    std::string readBuffer;
    std::string readHeader;
    long response_code;
    double elapsed;
    char* effective_url;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());

        struct curl_slist *hs = NULL;
        hs = curl_slist_append(hs, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &readHeader);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective_url);

        error = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        curl = NULL;

        if(error != 0) {
            Json::Value errorMessage;
            errorMessage["code"] = std::to_string(response_code);
            errorMessage["message"] = readBuffer;
            return errorMessage;
        }
        return JsonDecode(readBuffer);
    }
    return JsonDecode("");
}

Json::Value APIRouter::request(const std::string& baseURL) {
    switch(this->getMethod()) {
        case RequestMethod::get:
            std::cout << "I'm here GET" << std::endl;
            return this->get(baseURL);
        case RequestMethod::post:
            std::cout << "I'm here POST" << std::endl;
            return this->post(baseURL);
        case RequestMethod::patch:
            std::cout << "I'm here PATCH" << std::endl;
            return this->patch(baseURL);
        case RequestMethod::del:
            std::cout << "I'm here DEL" << std::endl;
            return this->del(baseURL);
    }
}

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

static Json::Value JsonDecode(const std::string& text) {
    Json::Value root;
    Json::Reader reader;
    bool result = reader.parse(text, root);
    if(!result){
        std::cout << "Error: " << text << std::endl;
    }
    return root;
}