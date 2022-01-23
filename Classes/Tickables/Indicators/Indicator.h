//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_INDICATOR_H
#define BROKERAPP_INDICATOR_H

#include <vector>
#include <string>
#include "../Tickable.h"
#include "../../Widgets/PlotItem/PlotItem.h"
#include "../../Nodes/UiNodeType.h"
#include "../../Nodes/NodeType.h"


class Indicator : public Tickable, public PlotItem {
public:
    explicit Indicator(Ticker* ticker);
    virtual ~Indicator();

    //TODO:: this is a main behavior and need attention
    /** For Now calculate will be called at onClose bar */
    virtual void calculate(BarHistory* barHistory);
    void onClose(BarHistory* barHistory) override;
    void onLoad(BarHistory* barHistory) override;
    void resetPlot() override;
    void reset() override;
    const ImVec4& getColor();
    const NodeType getNodeType();
    const UiNodeType getUiNodeType();

protected:
    UiNodeType _uiNodeType;
    NodeType _nodeType;
    ImVec4 _color{1, 1, 1, 1};

private:



};

#endif //BROKERAPP_INDICATOR_H
