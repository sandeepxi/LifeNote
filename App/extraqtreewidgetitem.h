#ifndef EXTRAQTREEWIDGETITEM_H
#define EXTRAQTREEWIDGETITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include "baseinfo.h"
class ExtraQTreeWidgetItem:public QTreeWidgetItem
{
public:

    ExtraQTreeWidgetItem(BaseInfo::NodeType type);
    //0 is normal
    //1 is deleted
    int deleteType = 0;
    //1 is recycleParentNode,defaule is 0
    bool isRecyleParent= 0;

    //this is to distinguish menu add note（新建笔记） or menu add node group（新建笔记本）
    BaseInfo::NodeType nodeType=BaseInfo::Child;
};


#endif // EXTRAQTREEWIDGETITEM_H
