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
    void readnodefile(QTreeWidget *tree_widget);//启动时，读取文件加载node
    void updateXml(OperationType type,QTreeWidgetItem *parentNode=NULL,QTreeWidgetItem *child=NULL);//节点发生改变时，重新生成配置文件
    void readnodefiletest();


};

#endif // NODECONFIG_H
