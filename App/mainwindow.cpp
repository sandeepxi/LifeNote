#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置左侧侧边栏样式
    ui->leftBar->setStyleSheet(QString("QAbstractButton{min-height:%1px;max-height:%1px;margin:0px;border:none;}").arg(17));
    ui->titleBar->setStyleSheet(QString("QAbstractButton{min-height:%1px;max-height:%1px;margin:0px;}").arg(25));

    ui->treeWidget->setColumnCount(1);

    ui->treeWidget->setHeaderLabels(QStringList()<<"first");
    //ui->treeWidget->setColumnWidth(0, 40);  //设置列宽
    ui->treeWidget->header()->setStretchLastSection(false);
    ui->treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    //隐藏标题栏
    ui->treeWidget->header()->setVisible(false);

    //设置背景色为透明
    ui->treeWidget->setStyleSheet("background-color:transparent;");
    setStyleSheet("QTreeWidget::item{""height:25px;""}");
    //设置不同层次菜单的缩进
    ui->treeWidget->setIndentation(15);
    //设置边框不可见
    ui->treeWidget->setFrameStyle(QFrame::NoFrame);

    //加载节点需要通过配置文件，而不是写死
    QTreeWidgetItem *rootItem_1 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *childItem_1_1 = new QTreeWidgetItem();
    QTreeWidgetItem *childItem_1_2 = new QTreeWidgetItem();
    QTreeWidgetItem *childItem_1_2_1 = new QTreeWidgetItem();

    QTreeWidgetItem *rootItem_2 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *childItem_2_1 = new QTreeWidgetItem();
    QTreeWidgetItem *childItem_2_2 = new QTreeWidgetItem();


    QTreeWidgetItem *rootItem_3 = new QTreeWidgetItem(ui->treeWidget);
    QTreeWidgetItem *childItem_3_1 = new QTreeWidgetItem();
    QTreeWidgetItem *childItem_3_2 = new QTreeWidgetItem();

    rootItem_1->setText(0,QObject::tr("笔记本"));
    childItem_1_1->setText(0,QObject::tr("每日工作"));
    childItem_1_2->setText(0,QObject::tr("节假日记"));
    childItem_1_2_1->setText(0,QObject::tr("人生感悟"));
    childItem_1_2_1->setForeground(0,QBrush(QColor(Qt::blue)));

    rootItem_2->setText(0,QObject::tr("收藏"));
    childItem_2_1->setText(0,QObject::tr("2022/10/09"));
    childItem_2_2->setText(0,QObject::tr("睡眠"));

    rootItem_3->setText(0,QObject::tr("废纸篓"));
    childItem_3_1->setText(0,QObject::tr("国际化"));
    childItem_3_2->setText(0,QObject::tr("pc直播"));

    ui->treeWidget->addTopLevelItem(rootItem_1);
    rootItem_1->addChild(childItem_1_1);
    rootItem_1->addChild(childItem_1_2);
    childItem_1_2->addChild(childItem_1_2_1);
    ui->treeWidget->addTopLevelItem(rootItem_2);
    rootItem_2->addChild(childItem_2_1);
    rootItem_2->addChild(childItem_2_2);

    ui->treeWidget->addTopLevelItem(rootItem_3);
    rootItem_3->addChild(childItem_3_1);
    rootItem_3->addChild(childItem_3_2);


    int size = ui->treeWidget->topLevelItemCount();
    QTreeWidgetItem *child;
    for (int i = 0; i < size; i++)
    {
        child = ui->treeWidget->topLevelItem(i);
        setItemIcon(child);
    }

    //设置左侧按钮icon
    ui->searchBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->searchBtn->setIcon(QIcon(":/res/icons/search.png"));

    //设置标题栏按钮
    ui->boldBtn->setIcon(QIcon(":/res/icons/bold.png"));
    ui->italicBtn->setIcon(QIcon(":/res/icons/italic.png"));
    ui->colorBtn->setIcon(QIcon(":/res/icons/color.png"));
    ui->underlineBtn->setIcon(QIcon(":/res/icons/underline.png"));


    //设置标题栏信号槽
    connect(ui->boldBtn,SIGNAL(clicked()),this,SLOT(boldBtn_clicked()));
    connect(ui->italicBtn,SIGNAL(clicked()),this,SLOT(italicBtn_clicked()));
    connect(ui->underlineBtn,SIGNAL(clicked()),this,SLOT(underlineBtn_clicked()));
    connect(ui->colorBtn,SIGNAL(clicked()),this,SLOT(colorBtn_clicked()));


}
void MainWindow::setItemIcon(QTreeWidgetItem* child)
{
    int childCount = child->childCount();
    if(childCount>0)
    {
         child->setIcon(0,QIcon(":/res/icons/parentnote.png"));
         for (int j = 0; j < childCount; ++j)
         {
             QTreeWidgetItem * grandson = child->child(j);
             if(grandson->childCount()>0)
             {
                 grandson->setIcon(0,QIcon(":/res/icons/parentnote.png"));
                 setItemIcon(grandson);
             }
             else
             {
                 grandson->setIcon(0,QIcon(":/res/icons/childnote.png"));
             }
         }
    }
    else
    {
         child->setIcon(0,QIcon(":/res/icons/childnote.png"));
    }

}

void MainWindow::boldBtn_clicked()
{
    QTextCharFormat fmt;
    if(ui->boldBtn->isChecked())
    {
        fmt.setFontWeight(QFont::Bold);
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);
    }
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::italicBtn_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->italicBtn->isChecked());
    ui->textEdit->mergeCurrentCharFormat(fmt);
}
void MainWindow::underlineBtn_clicked()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->underlineBtn->isChecked());
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::colorBtn_clicked()
{
    QColor color = QColorDialog::getColor(Qt::blue,this);
    if(color.isValid()){
        QTextCharFormat fmt;
        fmt=ui->textEdit->currentCharFormat();
        fmt.setForeground(color);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

