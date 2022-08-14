#include "svgtextlabel.h"
#include "ui_svgtextlabel.h"

SvgTextLabel::SvgTextLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SvgTextLabel)
{
    ui->setupUi(this);
}

SvgTextLabel::~SvgTextLabel()
{
    delete ui;
}

void SvgTextLabel::setSvgLabel(QString svgPath) {
    QSvgRenderer* svgRender = new QSvgRenderer();
    svgRender->load(svgPath);

    QPixmap* pixmap = new QPixmap(20,20);
    //pixmap->fill(Qt::transparent);//设置背景透明
    QPainter painter(pixmap);
    svgRender->render(&painter);
    _pixmap = pixmap;
    ui->labelSvg->setPixmap(*pixmap);
}

void SvgTextLabel::setText(QString str) {
    _strText = str;
    ui->labelText->setText(_strText);
}
