#include "util.h"

util::util()
{

}

//获取节点的路径
QString util::treeItemToFullPath(QTreeWidgetItem* treeItem)
{
    QString fullPath= treeItem->text(0);

    while (treeItem->parent() != NULL)
    {
        fullPath= treeItem->parent()->text(0) + "/" + fullPath;
        treeItem = treeItem->parent();
    }
    return fullPath;
}
