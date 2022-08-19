#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SvgTextLabel *todaySvgLabel=new SvgTextLabel;
    todaySvgLabel->setText("今日");
    todaySvgLabel->setSvgLabel(":/res/icons/today.svg");

    SvgTextLabel *saveSvgLabel=new SvgTextLabel;
    saveSvgLabel->setText("收藏");
    saveSvgLabel->setSvgLabel(":/res/icons/save.svg");

    SvgTextLabel *findSvgLabel=new SvgTextLabel;
    findSvgLabel->setText("搜索");
    findSvgLabel->setSvgLabel(":/res/icons/find.svg");

    ui->leftLayout->addWidget(todaySvgLabel);
    ui->leftLayout->addWidget(saveSvgLabel);
    ui->leftLayout->addWidget(findSvgLabel);
    QSpacerItem *sp= new QSpacerItem(20,500,QSizePolicy::Fixed,QSizePolicy::Minimum);
    ui->leftLayout->addSpacerItem(sp);

}

MainWindow::~MainWindow()
{
    delete ui;
}

