//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "../Tickables/Indicators/SMA.h"

SMANode::SMANode(std::shared_ptr<Indicator> sma):_indicator(std::move(sma)){
    setName("SMA Indicator");
    _idOutput = addOutput();
}

void SMANode::onRender(float dt) {

    if(auto indicator = _indicator.lock()) {
        auto sma = dynamic_cast<SMA*>(indicator.get());
        //set node's values from indicator
        if(sma->size() > 0)
            setValueForId(_idOutput, (*sma)[0]);

        ImNodes::BeginOutputAttribute(_idOutput);

        ImGui::Indent(40);
        ImGui::Text("output");
        ImNodes::EndOutputAttribute();
    }
}
