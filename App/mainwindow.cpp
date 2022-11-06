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
    initRecycleNode();
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
    connect(ui->pictureBtn,&QToolButton::clicked,this,&MainWindow::onPictureBtn_clicked);
    connect(ui->undoBtn,&QToolButton::clicked,this,&MainWindow::onUndoBtn_clicked);
    connect(ui->saveBtn,&QToolButton::clicked,this,&MainWindow::onSaveBtn_clicked);
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
    QTreeWidgetItem *newItem=new ExtraQTreeWidgetItem();
    QString newNodeName=util::NoRepeatNodeName(ui->treeWidget->currentItem());
    newItem->setText(0,newNodeName);
    auto currentNode=ui->treeWidget->currentItem();
    currentNode->addChild(newItem);
    config->updateXml(ADD,currentNode,newItem);
    //新增本地文件html
    QString dirpath=util::treeItemToNodeDirPath(newItem);
    QDir* dir = new QDir();
    if(!dir->exists(dirpath)){
        dir->mkpath(dirpath);
    }
    //创建本地空文档html
    QString filePath=util::treeItemToFullFilePath(newItem);
    QFile  myfile(filePath);
    //注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
    if (myfile.open(QFile::WriteOnly))
    {
        myfile.close();
    }
    setAllItemIcon();
}

//question：
//父节点变成子节点后，可以编辑内容，但是一新增内容又变成了父节点，内容丢失，这里需要改下

//右键菜单，删除笔记本操作
void MainWindow::onDeleteNoteItemClick()
{
    auto currentNode=ui->treeWidget->currentItem();
    auto currentPath= QCoreApplication::applicationDirPath();
    auto fullPath= util::treeItemToFullFilePath(currentNode); //如d:/sotrage/xxx.html
    bool isRecycle=currentNode->parent()->text(0)=="回收站"; //is recycle Node
    //if is recycleNode's child node ,delete directly
    if(isRecycle)
    {
        QFile file(fullPath);
        file.remove();
    }
    else
    {
        //若是非回收站的数据
        std::cout<<"delete menu"<<std::endl;
        if(currentNode->childCount()>0)
        {
            QMessageBox::warning(this, tr("警告"),tr("\n无法批量删除,请选中单个笔记进行删除!"),QMessageBox::Ok);
            return;
        }
        //移动本地存储文件到回收站
        QString fileName = util::treeItemToFileName(currentNode); //文件名称，如xxx.html
        auto recyclePath=QString("%1/storage/回收站/%2").arg(currentPath,fileName);
        bool moveResult= QFile::rename(fullPath,recyclePath); //A路径移动到B路径
        std::cout<<"delete node and move file "<<(moveResult ? "true": "false")  <<std::endl;
    }
    //delete doc(updateXml) must be ahead of the QTreeWidget'Node delete
    //because updateXml function is depend on the Node struct
    if(isRecycle)
    {
        config->updateXml(DELETE,currentNode);
    }
    else
    {
        config->updateXml(UPDATE,currentNode,recycleNode);
    }
    ExtraQTreeWidgetItem* extraCurrentNode= dynamic_cast<ExtraQTreeWidgetItem*>(currentNode);
    extraCurrentNode->deleteType=1;
    currentNode->parent()->removeChild(extraCurrentNode);//this line will trigger currentTreeItemChanged immediately
    extraCurrentNode->deleteType=0;
    if(!isRecycle) //if parentNode is recycle,not need to add
    {
       recycleNode->addChild(extraCurrentNode);
    }
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

//切换左侧节点时，保存上一个节点的内容，加载当前节点的内容
void MainWindow::currentTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    std::cout<<"currentTreeItemChanged tirggerd"<<std::endl;
    ExtraQTreeWidgetItem* extraPreviousNode= dynamic_cast<ExtraQTreeWidgetItem*>(previous);

    //save previous node content to local file
    //when delete node,the focus will be changed,and this function will be trigger.
    //so when the previous node is deleted, it's deletetype is 1 , don't save the previous node content.
    //otherwise, delete node, the local file will be create again.
    if(previous!=NULL&& extraPreviousNode->deleteType==0&&previous->childCount()==0)
    {
        auto previewFullPath=util::treeItemToFullFilePath(previous); //如d:/sotrage/xxx.html
        //解析出路径（不含文件名）和文件名
        int first = previewFullPath.lastIndexOf ("/");
        QString dirPath = previewFullPath.left (first); //文件夹路径

        //如果路径不存在，则创建
        QDir* dir = new QDir();
        if(!dir->exists(dirPath)){
            dir->mkpath(dirPath);
        }

        //创建一个输出文件的文档
        QFile  myfile(previewFullPath);
        //注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
        if (myfile.open(QFile::WriteOnly|QFile::Truncate))
        {
            QTextStream out(&myfile);
            out<<ui->textEdit->toHtml()<<Qt::endl;
        }
        myfile.close();
    }
    if(current==NULL||current->childCount()>0)
    {
        return;
    }
    //加载当前节点的内容
    auto fullPath=util::treeItemToFullFilePath(current);
    QFile file(fullPath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QByteArray allArray = file.readAll();
    QString allStr = QString(allArray);
    file.close();
    ui->textEdit->setHtml(allStr);
}

//给回收站node赋值
void MainWindow::initRecycleNode()
{
    int size = ui->treeWidget->topLevelItemCount();
    QTreeWidgetItem *child;
    for (int i = 0; i < size; i++)
    {
        child = ui->treeWidget->topLevelItem(i);
        if(child->text(0)=="回收站")
        {
            recycleNode=child;
            break;
        }
    }
}

//设置所有node的icon
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
    //InsertImageDialog();
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

void MainWindow::onPictureBtn_clicked()
{
    InsertImageDialog();
}

void MainWindow::onUndoBtn_clicked()
{

}

void MainWindow::onSaveBtn_clicked()
{
    if(ui->treeWidget->selectedItems().length()==0)
    {
        return;
    }
    if(ui->treeWidget->currentItem()->childCount()>0)
    {
        return;
    }
    QString fullPath=util::treeItemToFullFilePath(ui->treeWidget->currentItem());
    //解析出路径（不含文件名）和文件名
    int first = fullPath.lastIndexOf ("/");
    QString fileName = fullPath.right(fullPath.length ()-first-1); //xxxx.html
    QString dirPath = fullPath.left (first); //文件夹路径

    //如果路径不存在，则创建
    QDir* dir = new QDir();
    if(!dir->exists(dirPath)){
        dir->mkpath(dirPath);
    }

    //创建一个输出文件的文档
    QFile  myfile(fullPath);
    //注意WriteOnly是往文本中写入的时候用，ReadOnly是在读文本中内容的时候用，Truncate表示将原来文件中的内容清空
    if (myfile.open(QFile::WriteOnly|QFile::Truncate))
    {
        QTextStream out(&myfile);
        out<<ui->textEdit->toHtml()<<Qt::endl;
    }
}

void MainWindow::InsertImageDialog()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),
                                                ".", tr("Bitmap Files (*.bmp)\n"
                                                        "JPEG (*.jpg *jpeg)\n"
                                                        "GIF (*.gif)\n"
                                                        "PNG (*.png)\n"));
    QUrl Uri ( QString ( "file://%1" ).arg ( file ) );
    QImage image = QImageReader ( file ).read();

    QTextDocument * textDocument = ui->textEdit->document();
    textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextImageFormat imageFormat;
    imageFormat.setWidth( image.width() );
    imageFormat.setHeight( image.height() );
    imageFormat.setName( Uri.toString() );
    cursor.insertImage(imageFormat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

