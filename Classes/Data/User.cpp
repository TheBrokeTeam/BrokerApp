//
// Created by Maykon Meneghel on 24/02/22.
//

#include "User.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include <cstdio>
#include <utility>
#include "../Helpers/JsonUtils.h"
#include <fmt/format.h>

User::User(const std::string& id, const std::string& token)
{
    _id = id;
    _token = token;
}

User::User(const rapidjson::Document& obj) {
    _token = obj["token"].GetString();

    rapidjson::GenericObject user = obj["user"].GetObject();
    _id = user["_id"].GetString();
    _name = user["name"].GetString();
}

const char* User::GetName() {
    return _name.c_str();
}
