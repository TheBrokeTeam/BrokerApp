//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Context.h"

#include <utility>

Context::Context(Editor* editor): _editor(editor)
{
//    _httpServer = new HttpServer(9494);
    _dbManager = DBManager();

    if(std::filesystem::exists(Paths::UserData)) {
        rapidjson::Document user_doc;
        user_doc.SetObject();
        BAJson::parseFile(Paths::UserData, user_doc);
        _user = new User(user_doc);
    } else {
        _user = nullptr;
    }
}

void Context::updateData(float dt)
{

}

void Context::updateUI(float dt)
{
    for(auto& w : _widgets)
        w->update(dt);
}

const std::vector<std::shared_ptr<Widget>> &Context::getWidgets()
{
    return _widgets;
}

Editor *Context::getEditor()
{
    return _editor;
}

Indicator *Context::getIndicatorById(const std::string &id)
{
    for (const auto& indicator : _indicators)
    {
        if (indicator->getId() == id)
        {
            return indicator.get();
        }
    }
    return nullptr;
}

//Strategy *Context::getStrategyById(const std::string &id) {
//    for (const auto& strategy : _strategies)
//    {
//        if (strategy->getId() == id)
//        {
//            return strategy.get();
//        }
//    }
//    return nullptr;
//}

Indicator *Context::getIndicatorByName(const std::string &name)
{
    for (const auto& indicator : _indicators)
    {
        if (indicator->getName() == name)
        {
            return indicator.get();
        }
    }
    return nullptr;
}

//Strategy *Context::getStrategyByName(const std::string &name) {
//    for (const auto& strategy : _strategies)
//    {
//        if (strategy->getCode() == name)
//        {
//            return strategy.get();
//        }
//    }
//    return nullptr;
//}


void Context::setShouldRender(bool value)
{
    _shouldRender = value;
}

bool Context::getShouldRender() const
{
    return _shouldRender;
}

Context::~Context() {}

DBManager *Context::getDBManager()
{
    return &_dbManager;
}

//HttpServer* Context::getHttpServer()
//{
//    return _httpServer;
//}

bool Context::userExists()
{
    return (_user != nullptr);
}

User* Context::getUser()
{
    return _user;
}

void Context::saveUser(const rapidjson::Document& doc) {
    if(!std::filesystem::exists(Paths::Root))
    {
        std::filesystem::create_directory(Paths::Root);
    }

    if(!std::filesystem::exists(Paths::UserData))
    {
        BAJson::save(doc, Paths::UserData);
        loadUser();
    }
}

User* Context::loadUser()
{
    if(std::filesystem::exists(Paths::UserData)) {
        rapidjson::Document user_doc;
        user_doc.SetObject();
        BAJson::parseFile(Paths::UserData, user_doc);
        _user = new User(user_doc);
    } else {
        _user = nullptr;
    }
    return _user;
}

void Context::logout() {
    _sentAuthentication = false;
    _startingAuthentication = false;
    _user = nullptr;
}