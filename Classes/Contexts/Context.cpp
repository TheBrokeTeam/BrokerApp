//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Context.h"

Context::Context(Editor* editor): _editor(editor) {

}

void Context::updateData(float dt) {

}

void Context::updateUI(float dt) {
    for(auto& w : _widgets)
        w->update(dt);
}

const std::vector<std::shared_ptr<Widget>> &Context::getWidgets() {
    return _widgets;
}

Editor *Context::getEditor() {
    return _editor;
}

Indicator *Context::getIndicatorById(const std::string &id) {
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

Indicator *Context::getIndicatorByName(const std::string &name) {
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


void Context::setShouldRender(bool value) {
    _shouldRender = value;
}

bool Context::getShouldRender() const {
    return _shouldRender;
}