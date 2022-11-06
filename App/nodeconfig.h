#ifndef NODECONFIG_H
#define NODECONFIG_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>
#include <vector>
#include <QTreeWidgetItem>
#include <QDomElement>
#include <iostream>
#include "util.h"
class nodeconfig
{
public:
    nodeconfig();
    void readNodeConfigXML(QTreeWidget *tree_widget);//启动时，读取文件加载node
    //currentNode is The node that is being operated
    //newNode is the Node in the Add  OperationType
    void updateXml(OperationType type,QTreeWidgetItem *currenttNode,QTreeWidgetItem *newNode=NULL);//节点发生改变时，重新生成配置文件
};

#endif // NODECONFIG_H
