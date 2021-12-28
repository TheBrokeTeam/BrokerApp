//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CONTEXTUALIZABLE_H
#define BROKERAPP_CONTEXTUALIZABLE_H

class Context;
class Contextualizable {
public:
    Context* getContext();
protected:
    void setContext(Context*);

private:
    Context* _context{nullptr};
};


#endif //BROKERAPP_CONTEXTUALIZABLE_H
