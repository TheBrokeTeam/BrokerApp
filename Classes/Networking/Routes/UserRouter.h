//
// Created by Maykon Meneghel on 10/01/22.
//

#ifndef UNTITLED1_USERROUTER_H
#define UNTITLED1_USERROUTER_H

#include <string>
#include <map>
#include "../APIRouter.h"

class UserRouter {
protected:
    std::string endpoint = "/users";
public:
    UserRouter();
    [[nodiscard]] APIRouter getAuthorization(Json::Value body) const;
    [[nodiscard]] APIRouter createOne(Json::Value) const;
    [[nodiscard]] APIRouter updateOne() const;
    [[nodiscard]] APIRouter deleteOne() const;
};


#endif //UNTITLED1_USERROUTER_H
