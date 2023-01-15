#ifndef SVGTEXTLABEL_H
#define SVGTEXTLABEL_H

#include <QWidget>
#include <QtSvg>

namespace Ui {
class SvgTextLabel;
}

class SvgTextLabel : public QWidget
{
    Q_OBJECT

public:
    explicit SvgTextLabel(QWidget *parent = nullptr);
    ~SvgTextLabel();
    void setSvgLabel(QString svgPath);
    void setText(QString str);

private:
    Ui::SvgTextLabel *ui;
    QPixmap* _pixmap;
    QString _strText;

};

#endif // SVGTEXTLABEL_H
