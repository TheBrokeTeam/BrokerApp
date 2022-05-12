//
// Created by Luiz Veloso on 13/04/22.
//

#ifndef BROKERAPP_ORDERLOGTABLE_H
#define BROKERAPP_ORDERLOGTABLE_H

#include <string>;

class OrderLogTab {
    std::string tableName;
    virtual void buildTable() = 0;
    virtual void populateTableRow() = 0;
};


#endif //BROKERAPP_ORDERLOGTABLE_H
