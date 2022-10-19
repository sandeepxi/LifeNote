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

    //通过配置文件，创建node
    config->readnodefile(ui->treeWidget);

    setAllItemIcon();

    //设置左侧按钮icon
    ui->searchBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->searchBtn->setIcon(QIcon(":/res/icons/search.png"));

    //设置标题栏按钮
    ui->boldBtn->setIcon(QIcon(":/res/icons/bold.png"));
    ui->italicBtn->setIcon(QIcon(":/res/icons/italic.png"));
    ui->colorBtn->setIcon(QIcon(":/res/icons/color.png"));
    ui->underlineBtn->setIcon(QIcon(":/res/icons/underline.png"));

    initRightMenu();

    //设置标题栏信号槽
    connect(ui->boldBtn,SIGNAL(clicked()),this,SLOT(boldBtn_clicked()));
    connect(ui->italicBtn,SIGNAL(clicked()),this,SLOT(italicBtn_clicked()));
    connect(ui->underlineBtn,SIGNAL(clicked()),this,SLOT(underlineBtn_clicked()));
    connect(ui->colorBtn,SIGNAL(clicked()),this,SLOT(colorBtn_clicked()));
    connect(ui->treeWidget,&QTreeWidget::currentItemChanged,this,&MainWindow::currentTreeItemChanged);
    connect(ui->treeWidget,&QTreeWidget::itemPressed,this,&MainWindow::right_item_pressed);
    connect(newNoteAction, SIGNAL(triggered(bool)), this , SLOT(onNewNoteItemClick()));
    connect(saveNoteAction, SIGNAL(triggered(bool)), this , SLOT(onSaveNoteItemClick()));
    connect(moveNoteAction, SIGNAL(triggered(bool)), this , SLOT(onMoveNoteItemClick()));
    connect(lockAction, SIGNAL(triggered(bool)), this , SLOT(onLockItemClick()));
    connect(deleteNoteAction, SIGNAL(triggered(bool)), this , SLOT(onDeleteNoteItemClick()));
}

//初始化treewidget 右键菜单
void MainWindow::initRightMenu()
{
    newNoteAction = new QAction("新建笔记", ui->treeWidget);
    saveNoteAction = new QAction("收藏笔记", ui->treeWidget);
    moveNoteAction = new QAction("移动笔记", ui->treeWidget);
    lockAction = new QAction("添加密码锁", ui->treeWidget);
    deleteNoteAction = new QAction("删除笔记", ui->treeWidget);
    rightMenu=new QMenu(ui->treeWidget);
    rightMenu->addAction(newNoteAction);
    rightMenu->addAction(saveNoteAction);
    rightMenu->addAction(moveNoteAction);
    rightMenu->addAction(lockAction);
    rightMenu->addAction(deleteNoteAction);
}

//右键菜单，新增笔记本操作
void MainWindow::onNewNoteItemClick()
{
    if(ui->treeWidget->currentItem()==NULL)
    {
        return;
    }
    QTreeWidgetItem *newItem=new QTreeWidgetItem();
    newItem->setText(0,"无标题");
    auto currentNode=ui->treeWidget->currentItem();
    currentNode->addChild(newItem);
    config->updateXml(ADD,currentNode,newItem);
    setAllItemIcon();
}

//右键菜单，删除笔记本操作
void MainWindow::onDeleteNoteItemClick()
{
    std::cout<<"delete menu"<<std::endl;
    auto currentNode=ui->treeWidget->currentItem();
    //此处需要先删除doc，因为updateXml中依赖node结构，不能先删node
    config->updateXml(DELETE,currentNode,NULL);
    currentNode->parent()->removeChild(currentNode);
    setAllItemIcon();
}

void MainWindow::onSaveNoteItemClick()
{
    std::cout<<"save menu"<<std::endl;
}

void MainWindow::onMoveNoteItemClick()
{
    std::cout<<"move menu"<<std::endl;
}

void MainWindow::onLockItemClick()
{
    std::cout<<"lock menu"<<std::endl;
}



void MainWindow::right_item_pressed(QTreeWidgetItem *item, int column)
{
    if(QGuiApplication::mouseButtons()!= Qt::RightButton)
    {
        return;
    }
    std::cout<<"right clicked"<<std::endl;
    rightMenu->exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
}

void MainWindow::currentTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
     QString str("aaaaa");
     std::cout<<str.toStdString()<<std::endl;
     if(current->childCount()>0)
     {
         return;
     }
}

void MainWindow::setAllItemIcon()
{
    int size = ui->treeWidget->topLevelItemCount();
    QTreeWidgetItem *child;
    for (int i = 0; i < size; i++)
    {
        child = ui->treeWidget->topLevelItem(i);
        setItemIcon(child);
    }
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

