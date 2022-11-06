#ifndef EXTRAQTREEWIDGETITEM_H
#define EXTRAQTREEWIDGETITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class ExtraQTreeWidgetItem:public QTreeWidgetItem
{
public:
    enum NodeType
    {
        NodeChild,
        NodeParent,
    };
    ExtraQTreeWidgetItem(NodeType type);
    //0 is normal
    //1 is deleted
    int deleteType = 0;
    //1 is recycleParentNode,defaule is 0
    bool isRecyleParent= 0;
    NodeType nodeType=NodeChild;
};


#endif // EXTRAQTREEWIDGETITEM_H
