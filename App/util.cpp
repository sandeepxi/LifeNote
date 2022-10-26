#include "util.h"

util::util()
{

}

//获取节点的路径path,如 笔记本/每日工作
QString util::treeItemToNodePath(QTreeWidgetItem* treeItem)
{
    QString fullPath= treeItem->text(0);

    while (treeItem->parent() != NULL)
    {
        fullPath= treeItem->parent()->text(0) + "/" + fullPath;
        treeItem = treeItem->parent();
    }
    return fullPath;
}

//返回本地存储文件名，如工作.html
QString util::treeItemToFileName(QTreeWidgetItem* treeItem)
{
    auto path=treeItemToFullFilePath(treeItem);
    int first = path.lastIndexOf ("/");
    QString fileName = path.right(path.length()-first-1); //文件名称，如xxx.html
    return fileName;
}

QString util::treeItemToFullFilePath(QTreeWidgetItem* treeItem)//返回完整地存储路径，如D://笔记本/工作.html
{
    auto currentPath= QCoreApplication::applicationDirPath();
    //保存上一个节点的内容
    QString nodePath=treeItemToNodePath(treeItem);
    return QString("%1/storage/%2.html").arg(currentPath,nodePath);
}
