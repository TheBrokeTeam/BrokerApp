//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CONTEXTUALIZABLE_H
#define BROKERAPP_CONTEXTUALIZABLE_H

class Context;
class Contextualizable {
public:
    Contextualizable(Context* context);

    Context* getContext();

protected:
    Context* _context{nullptr};
};


#endif //BROKERAPP_CONTEXTUALIZABLE_H
