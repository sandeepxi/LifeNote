#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QTreeWidgetItem>

enum OperationType
{
   ADD,
   DELETE,
   UPDATE,
};
class util
{
public:
    util();
    static QString treeItemToFullPath(QTreeWidgetItem* treeItem);
};

#endif // UTIL_H
