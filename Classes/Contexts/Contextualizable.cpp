//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Contextualizable.h"
#include "Context.h"

Context* Contextualizable::getContext(){
    return _context;
}

void Contextualizable::setContext(Context *context) {
    _context = context;
}
