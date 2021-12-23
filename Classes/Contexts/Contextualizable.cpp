//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Contextualizable.h"
#include "Context.h"

Contextualizable::Contextualizable(Context *context): _context(context){}

Context* Contextualizable::getContext(){
    return _context;
}