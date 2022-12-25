#include "nodeconfig.h"
#include "extraqtreewidgetitem.h"

nodeconfig::nodeconfig()
{

}
struct node_info
{
    QString node_name;
    ExtraQTreeWidgetItem *widgetitem;
};

//currentNode is The node that is being operated
//newNode is the Node in the Add  OperationType and UPDATE
void nodeconfig::updateXml(OperationType type,QTreeWidgetItem *currentNode,QTreeWidgetItem *newNode)
{
    QFile file("../../../config/node.xml");

    if(!file.open(QIODevice::ReadOnly))
    {
        std::cout<<"open local xml failed";
        return;
    }
    QDomDocument doc;
    if(!doc.setContent(&file))//从字节数组中解析XML文档，并将其设置为文档的内容
    {
        std::cout<<"set doc content form file failed";
        file.close();
        return;
    }
    file.close();
    if(type==AddNode)
    {
        QDomNodeList list = doc.elementsByTagName(currentNode->text(0));
        auto path=util::treeItemToNodePath(currentNode);
        for(int i=0;i<list.size();i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute("path")==path)
            {
                QDomElement newDomElement=doc.createElement(newNode->text(0));
                list.at(i).appendChild(newDomElement);
                newDomElement.setAttribute("path",util::treeItemToNodePath(newNode));
                newDomElement.setAttribute("nodetype","0");
                break;
            }
        }
    }
    else if(type==AddNodeGroup)
    {
        QDomNodeList list = doc.elementsByTagName(currentNode->text(0));
        auto path=util::treeItemToNodePath(currentNode);
        for(int i=0;i<list.size();i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute("path")==path)
            {
                QDomElement newDomElement=doc.createElement(newNode->text(0));
                list.at(i).appendChild(newDomElement);
                newDomElement.setAttribute("path",util::treeItemToNodePath(newNode));
                newDomElement.setAttribute("nodetype","1");
                break;
            }
        }
    }
    else if(type==DeleteNode)
    {
        QDomNodeList list = doc.elementsByTagName(currentNode->text(0));
        auto path=util::treeItemToNodePath(currentNode);
        for(int i=0;i<list.size();i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute("path")==path)
            {
                e.parentNode().removeChild(e);
                break;
            }
        }
    }
    else if(type==MoveNode)
    {
        QDomNodeList list = doc.elementsByTagName(currentNode->text(0));
        auto path=util::treeItemToNodePath(currentNode);
        QDomElement updateDomElement;
        for(int i=0;i<list.size();i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute("path")==path)
            {
                updateDomElement=e;
                e.parentNode().removeChild(e);
                break;
            }
        }
        QDomNodeList listTargetNode = doc.elementsByTagName(newNode->text(0));
        auto TargetPath=util::treeItemToNodePath(newNode);
        for(int i=0;i<listTargetNode.size();i++)
        {
            QDomElement e = listTargetNode.at(i).toElement();
            if(e.attribute("path")==TargetPath)
            {
                e.appendChild(updateDomElement);
                break;
            }
        }
    }
    if(!file.open(QFile::WriteOnly|QFile::Truncate))//重写文件，如果不用truncate就是在后面追加内容，就无效了
    {
        return;
    }
    QTextStream out_stream(&file);
    doc.save(out_stream,4);
    file.close();
}

//XML struct is seem like qtreeWidget ,is a tree
//The node is added to the treewidget by loop the xml document
void nodeconfig::readNodeConfigXML(QTreeWidget *tree_widget)
{
    //设置输入文件
    QFile inputfile("../../../config/node.xml");
    qDebug()<<QDir::currentPath();
    if(!inputfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open node.xml file failed";
        return ;
    }
    QXmlStreamReader reader(&inputfile);
    std::vector<node_info*> vector_node;
    //开始解析
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        switch (token)
        {
        case QXmlStreamReader::StartDocument:
            break;
        case QXmlStreamReader::EndDocument:
            break;
        case QXmlStreamReader::StartElement:
            if(!reader.name().toString().isEmpty())
            {
                node_info *node = new node_info();
                node->node_name=reader.name().toString();
                ExtraQTreeWidgetItem::NodeType isParent=ExtraQTreeWidgetItem::NodeChild;
                foreach (const QXmlStreamAttribute & attribute, reader.attributes())
                {
                    qDebug()<<attribute.name();
                    qDebug()<<attribute.value();
                    if(attribute.name().toString()=="nodetype")
                    {
                        isParent= attribute.value().toString()=="0"?ExtraQTreeWidgetItem::NodeChild:ExtraQTreeWidgetItem::NodeParent;
                        break;
                    }
                }
                node->widgetitem=new ExtraQTreeWidgetItem(isParent);
                if( node->node_name=="root")
                {
                    continue;
                }
                if(vector_node.size()==0)
                {
                    tree_widget->addTopLevelItem(node->widgetitem);
                }
                else if(vector_node.size()>0)
                {
                    auto preview_node=vector_node.at(vector_node.size()-1);
                    preview_node->widgetitem->addChild(node->widgetitem);
                }
                vector_node.push_back(node);
                node->widgetitem->setText(0,node->node_name);
            }
            break;
        case QXmlStreamReader::EndElement:
            if(reader.name().toString()=="root")
            {
                continue;
            }
            if(vector_node.size()>0)
            {
                //delete last node of vector，then we can always get the parent through previousNode
                vector_node.pop_back();
            }
            break;
        case QXmlStreamReader::Characters:
//            if(vector_node.size()>0)
//            {
//                QString type= reader.text().toString();
//                auto lastNode=vector_node.at(vector_node.size()-1);
//                lastNode->widgetitem->nodeType= type=="0"?ExtraQTreeWidgetItem::NodeChild:ExtraQTreeWidgetItem::NodeParent;
//            }
            break;
        }
    }

    //是否是正常结束
    if (reader.error())
    {
        qDebug() << "Error: " << reader.errorString() << "in file test.xml at line " << reader.lineNumber() << ", column " << reader.columnNumber();
        return ;
    }

    //关闭文件
    inputfile.close();
    return;
}


