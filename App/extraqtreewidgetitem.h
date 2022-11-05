#ifndef EXTRAQTREEWIDGETITEM_H
#define EXTRAQTREEWIDGETITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class ExtraQTreeWidgetItem:public QObject, public QTreeWidgetItem
{
public:
    ExtraQTreeWidgetItem();
    //o is normal
    //1 is deleted
    int deleteType=0;
};


#endif // EXTRAQTREEWIDGETITEM_H
