//
// Created by Luiz Veloso on 21/01/22.
//

#include "EMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "NodeType.h"
#include "UiNodeType.h"


EMANode::EMANode(std::shared_ptr<Indicator> ema,StrategyEditor* nodeEditor): BaseNode(ema, nodeEditor) {}


void EMANode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto smaShared = getIndicator();
    if(!smaShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &ema = *dynamic_cast<EMA *>(smaShared.get());

    if (ema.size() > 0)
        stack.push(ema(0));
    else
        stack.push(0.0f);

}
