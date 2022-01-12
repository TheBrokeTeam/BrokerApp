//
// Created by Arthur Abel Motelevicz on 06/01/22.
//

#ifndef BROKERAPP_NODESLIST_H
#define BROKERAPP_NODESLIST_H


#include "Widget.h"
#include <implot.h>
#include <implot_internal.h>
#include <vector>
#include "../Helpers/PlotHelper.h"
#include "../Nodes/INode.h"
#include "../Editor.h"

class NodesList : public Widget{
public:
    typedef std::function<void(void)> TrashClickCallback;

    static inline const char* NODES_DRAG_ID = "NODES_ID";
    static inline const char* NODES_DRAG_ID_REMOVING = "NODES_ID_REMOVING";

    struct DragAndDropNodeItem {
        UiNodeType type;
        Editor::Icons icon;
        std::string desc{""};
        DragAndDropNodeItem(UiNodeType type): type(type){
            switch (type) {
                case UiNodeType::CROSS:
                    icon = Editor::Icons::node_cross;
                    desc = "Cross Node: the output is true only when the A crosses B (up or down), otherwise stays false.\nUse case: used for cross SMA triggers.";
                    break;
                case UiNodeType::COUNTER:
                    icon = Editor::Icons::node_counter;
                    desc = "Counter Node: count each time A is different from zero.\nUse case: use for count cross from Cross Node.";
                    break;
                case UiNodeType::TREND:
                    icon = Editor::Icons::node_trend;
                    desc = "Trend Node: the output is true when is trending (down or up),otherwise stays false.\nUse case: combine with cross SMA.";
                    break;
                case UiNodeType::TRADE:
                    icon = Editor::Icons::node_trade;
                    desc = "Trade Node: when A is true or more than 0, open a position (shorting or longing).";
                    break;
                case UiNodeType::BAR_SEQ_DOWN:
                    icon = Editor::Icons::node_bar_seq_down;
                    desc = "Down Sequence Node: Identify N numbers of negative bars in sequence.";
                    break;
                case UiNodeType::BAR_SEQ_UP:
                    icon = Editor::Icons::node_bar_seq_up;
                    desc = "Up Sequence Node: Identify N numbers of positive bars in sequence.";
                    break;
                default:
                    break;
            }
        }
    };

    NodesList(Context* context);

    void updateVisible(float dt) override;
    std::vector<DragAndDropNodeItem>& getNodes();
    void onPushStyleVar() override;
    void setTrashCallback(TrashClickCallback callback);

private:
    TrashClickCallback _trashCallback;
    void drawView();
    const int _numberOfItems = 4;
    std::vector<DragAndDropNodeItem>  _dragAndDropItems;
};



#endif //BROKERAPP_NODESLIST_H