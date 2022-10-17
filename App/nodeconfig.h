#ifndef NODECONFIG_H
#define NODECONFIG_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QDir>
#include <vector>
#include<QTreeWidgetItem>
class nodeconfig
{
public:
    nodeconfig();
    void readnodefile(QTreeWidget *tree_widget);
    void readnodefiletest();


};

#endif // NODECONFIG_H
