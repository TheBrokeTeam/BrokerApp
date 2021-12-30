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
