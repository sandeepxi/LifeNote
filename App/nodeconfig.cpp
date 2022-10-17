#include "nodeconfig.h"

nodeconfig::nodeconfig()
{

}
struct node_info
{
    QString node_name;
    bool isclose;
    QTreeWidgetItem *widgetitem;
};

void nodeconfig::readnodefile(QTreeWidget *tree_widget)
{
    //设置输入文件
    QFile inputfile("config/node.xml");
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
                node->isclose=false;
                node->node_name=reader.name().toString();
                node->widgetitem=new QTreeWidgetItem();
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
            if(vector_node.capacity()>0)
            {
                vector_node.pop_back();//删掉最后一个
            }
            break;
        case QXmlStreamReader::Characters:


            break;
        default:
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

void nodeconfig::readnodefiletest()
{
    //设置输入文件
    QFile inputfile("config/node1.xml");
    qDebug()<<QDir::currentPath();
    if(!inputfile.open(QIODevice::ReadOnly))
    {
        qDebug() << "Open input file failed";
        return ;
    }
    QXmlStreamReader reader(&inputfile);

    //设置输出文件
    QFile outputfile;
    if(!outputfile.open(stdout, QIODevice::WriteOnly))
    {
        qDebug() << "Open output file failed";
        return ;
    }
    QXmlStreamWriter writer(&outputfile);
    writer.setAutoFormatting(true);

    //开始解析
    while (!reader.atEnd())
    {
        QXmlStreamReader::TokenType token = reader.readNext();
        switch (token)
        {
        case QXmlStreamReader::StartDocument:
            writer.writeStartDocument();
            break;
        case QXmlStreamReader::EndDocument:
            writer.writeEndDocument();
            break;
        case QXmlStreamReader::StartElement:
            if(reader.name() == QString::fromStdString("xbel"))
            {
                writer.writeStartElement(reader.name().toString());
                writer.writeAttribute("version", reader.attributes().value("version").toString());
            }
            else if(reader.name() == QString::fromStdString("folder"))
            {
                writer.writeStartElement(reader.name().toString());
                writer.writeAttribute("folded", reader.attributes().value("folded").toString());
            }
            else if(reader.name() == QString::fromStdString("title"))
            {
                writer.writeStartElement(reader.name().toString());
            }
            else if(reader.name() == QString::fromStdString("bookmark"))
            {
                writer.writeStartElement(reader.name().toString());
                writer.writeAttribute("href", reader.attributes().value("href").toString());
            }
            break;
        case QXmlStreamReader::EndElement:
            writer.writeEndElement();
            break;
        case QXmlStreamReader::Characters:
            writer.writeCharacters(reader.text().toString());
            break;
        default:
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
    outputfile.flush();
    outputfile.close();
    return;
}
