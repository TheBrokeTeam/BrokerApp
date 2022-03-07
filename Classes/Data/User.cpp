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

User::User(std::string id): id_(std::move(id))
{

}

User* User::User_= nullptr;

User *User::GetInstance(const std::string& id){
    return new User(id);
}

std::string User::id() const {
    return id_;
}