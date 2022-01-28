//
// Created by Maykon Meneghel on 07/01/22.
//

#include "APIRouter.h"
#include <utility>
#include "curl//curl.h"
#include "curl/easy.h"
#include <iostream>
#include <rapidjson/document.h>
#include <zip_file.hpp>
#include <filesystem>
#include <iomanip>
#include <filesystem>


APIRouter::APIRouter(RequestMethod method, std::string path) {
    this->method = method;
    this->path = std::move(path);
    this->body = "";
}

std::string APIRouter::getPath() {
    return this->path;
}

RequestMethod APIRouter::getMethod() {
    return this->method;
}

std::string APIRouter::getBody() {
    return this->body;
}

void APIRouter::setBody(std::string newBody) {
    this->body = std::move(newBody);
}

rapidjson::Document APIRouter::get(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    std::cout << endpoint << std::endl;
    CURL *curl;
    CURLcode error;

    rapidjson::Document documentResponse;
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

        documentResponse.Parse(readBuffer.c_str());
        return documentResponse;
    }

    documentResponse.SetObject();
    rapidjson::Document::AllocatorType& allocator = documentResponse.GetAllocator();
    documentResponse.AddMember("message", "CURL Error", allocator);
    return documentResponse;
}

rapidjson::Document APIRouter::post(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    rapidjson::Document documentResponse;
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

        std::string bodyString = this->getBody();
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

        documentResponse.Parse(readBuffer.c_str());
        return documentResponse;
    }

    documentResponse.SetObject();
    rapidjson::Document::AllocatorType& allocator = documentResponse.GetAllocator();
    documentResponse.AddMember("message", "CURL Error", allocator);
    return documentResponse;
}

rapidjson::Document APIRouter::patch(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    rapidjson::Document documentResponse;
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

        documentResponse.Parse(readBuffer.c_str());
        return documentResponse;
    }

    documentResponse.SetObject();
    rapidjson::Document::AllocatorType& allocator = documentResponse.GetAllocator();
    documentResponse.AddMember("message", "CURL Error", allocator);
    return documentResponse;
}

rapidjson::Document APIRouter::del(const std::string& baseURL) {
    std::string endpoint = baseURL + this->getPath();

    CURL *curl;
    CURLcode error;

    rapidjson::Document documentResponse;
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

        documentResponse.Parse(readBuffer.c_str());
        return documentResponse;
    }

    documentResponse.SetObject();
    rapidjson::Document::AllocatorType& allocator = documentResponse.GetAllocator();
    documentResponse.AddMember("message", "CURL Error", allocator);
    return documentResponse;
}

rapidjson::Document APIRouter::request(const std::string& baseURL) {
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

void APIRouter::download(const std::string &baseURL, const Symbol::Path& filepath) {
        std::string endpoint = baseURL + this->getPath();

        std::cout << endpoint << std::endl;
        CURL *curl;
        FILE *fp;
        CURLcode res_code;

        std::string response;
        std::string readBuffer;
        std::string readHeader;
        long response_code;
        double elapsed;
        char* effective_url;

        curl = curl_easy_init();

        if(curl) {
            curl_easy_setopt(curl, CURLOPT_URL, endpoint.c_str());

            struct curl_slist *hs = NULL;
            hs = curl_slist_append(hs, "Content-Type: application/zip");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);

            curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);

            fp = fopen(filepath.zip_filename.c_str(), "wb");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &effective_url);

            res_code = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);
            curl = NULL;

            if(res_code == CURLE_OK && response_code == 0) {
                std::cout << "Tudo certo por aqui.." << std::endl;
                try {
                    miniz_cpp::zip_file file(filepath.zip_filename);
                    file.extractall(filepath.dirname);

                    std::filesystem::remove(filepath.zip_filename);
//                    rapidcsv::Document doc(file.getinfo(0).filename, rapidcsv::LabelParams(-1, -1));

                    //std::vector<float> close = doc.GetColumn<float>(5);
                    //std::cout << "Read " << close.size() << " values." << std::endl;

                } catch(std::exception exception){
                    std::cout << exception.what() << std::endl;
                    std::cout << "File is Empty" << std::endl;
                    std::filesystem::remove(filepath.zip_filename);
                }
            } else {
                std::cout << "Problema com a requisição do ZIP" << std::endl;
            }
        }
}

static size_t WriteCallback(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}
