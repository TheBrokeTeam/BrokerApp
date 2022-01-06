////
//// Created by Arthur Abel Motelevicz on 03/01/22.
////
//
//#include "CrossNode.h"
//#include <imgui.h>
//#include <imnodes.h>
//#include "../Editor.h"
//
//
//CrossNode::CrossNode() {
//    setName("Cross");
//    _idInput1 = addInput();
//    _idInput2 = addInput();
//    _idOuput = addOutput();
//}
//
//void CrossNode::onRender(float dt) {
//    //initial update
//    _currentInput1 = getValueFromId(_idInput1);
//    _currentInput2 = getValueFromId(_idInput2);
//
//    //do the logic
//    if(_isCrossUp)
//        _output = _currentInput2 > _currentInput1 && _lastInput2 < _lastInput1;
//    else
//        _output = _currentInput2 < _currentInput1 && _lastInput2 > _lastInput1;
//
//
//    if(_currentInput1 > 0 && _currentInput2 > 0)
//        setValueForId(_idOuput, _output);
//
//    //render node
//    ImNodes::BeginInputAttribute(_idInput1);
//    ImGui::Text("input 1");
//    ImGui::SameLine();
//    ImGui::Checkbox("Cross up",&_isCrossUp);
//    ImNodes::EndInputAttribute();
//
//    ImNodes::BeginInputAttribute(_idInput2);
//    ImGui::Text("input 2");
//    ImGui::Dummy(ImVec2(100,5));
//    ImNodes::EndInputAttribute();
//
//    ImNodes::BeginOutputAttribute(_idOuput);
//    ImGui::Indent(ImGui::GetItemRectSize().x);
//    ImGui::Text("output");
//    ImNodes::EndInputAttribute();
//
//    //final update
//    _lastInput1 = _currentInput1;
//    _lastInput2 = _currentInput2;
//}
//
//CrossNode::~CrossNode() {}
