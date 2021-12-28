//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Contextualizable.h"
#include "Context.h"

Context* Contextualizable::getContext(){
    assert(_context != nullptr && "Set context  probably not called from its subclass");
    return _context;
}

void Contextualizable::setContext(Context * context) {
    _context =  context;
}
