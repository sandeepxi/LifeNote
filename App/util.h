#ifndef UTIL_H
#define UTIL_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QCoreApplication>
enum OperationType
{
   AddNode,
   AddNodeGroup,
   DeleteNode,
   MoveNode,
};


class util
{
public:
    util();
    static QString treeItemToNodeDirPath(QTreeWidgetItem* treeItem);//返回path,如 笔记本/每日工作
    static QString treeItemToNodePath(QTreeWidgetItem* treeItem);//返回path,如 笔记本/每日工作
    static QString treeItemToFileName(QTreeWidgetItem* treeItem);//返回本地存储文件名，如工作.html
    static QString treeItemToFullFilePath(QTreeWidgetItem* treeItem);//返回本地存储路径，如D://笔记本/工作.html
    static QString NoRepeatNodeName(QTreeWidgetItem* parentNode);
};

#endif // UTIL_H
