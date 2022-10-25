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
#include<iostream>
#include<QMenu>
#include<QTextDocumentFragment>
#include<QFileDialog>
#include<QImageReader>
#include "nodeconfig.h"
#include "util.h"


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
    QAction * newNoteAction;
    QAction * deleteNoteAction;
    QAction * saveNoteAction;
    QAction * moveNoteAction;
    QAction * lockAction;
    nodeconfig *config ;

    QMenu *rightMenu;
    void setAllItemIcon();
    void setItemIcon(QTreeWidgetItem* child_item);
    void initRightMenu();
    void InsertImageDialog();
public slots:
    void boldBtn_clicked();
    void italicBtn_clicked();
    void underlineBtn_clicked();
    void colorBtn_clicked();
    void onPictureBtn_clicked();
    void onUndoBtn_clicked();
    void onSaveBtn_clicked();
    void right_item_pressed(QTreeWidgetItem *item, int column);//右键菜单点击
    void currentTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

    void onNewNoteItemClick();
    void onSaveNoteItemClick();
    void onMoveNoteItemClick();
    void onLockItemClick();
    void onDeleteNoteItemClick();
};
#endif // MAINWINDOW_H
