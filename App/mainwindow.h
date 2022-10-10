#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMessageBox>
//#include "svgtextlabel.h"
#include<QSpinBox>
#include<QColorDialog>
#include<QTreeWidget>
#include<QTreeWidgetItem>
#include<QStandardItemModel>
#include<QStandardItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void boldBtn_clicked();
    void italicBtn_clicked();
    void underlineBtn_clicked();
    void colorBtn_clicked();

};
#endif // MAINWINDOW_H
