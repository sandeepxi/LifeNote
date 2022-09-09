#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // this->setWindowFlags(Qt::FramelessWindowHint);
    //设置左侧侧边栏样式
    ui->leftBar->setStyleSheet(QString("QAbstractButton{min-height:%1px;max-height:%1px;margin:0px;border:none;}").arg(17));
    ui->titleBar->setStyleSheet(QString("QAbstractButton{min-height:%1px;max-height:%1px;margin:0px;}").arg(25));

    //设置左侧按钮icon
    ui->todayBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->todayBtn->setIcon(QIcon(":/res/icons/today.png"));
    ui->saveBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->saveBtn->setIcon(QIcon(":/res/icons/save.png"));
    ui->searchBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->searchBtn->setIcon(QIcon(":/res/icons/search.png"));
    ui->recycleBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->recycleBtn->setIcon(QIcon(":/res/icons/recycle.png"));

    //设置标题栏按钮
    ui->boldBtn->setIcon(QIcon(":/res/icons/bold.png"));
    ui->italicBtn->setIcon(QIcon(":/res/icons/italic.png"));
    ui->colorBtn->setIcon(QIcon(":/res/icons/color.png"));
    ui->underlineBtn->setIcon(QIcon(":/res/icons/underline.png"));
    ui->deletelineBtn->setIcon(QIcon(":/res/icons/deleteline.png"));
    connect(ui->boldBtn,SIGNAL(clicked()),this,SLOT(boldBtn_clicked()));
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

MainWindow::~MainWindow()
{
    delete ui;
}

