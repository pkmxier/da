#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QBoxLayout"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QMovie>
#include <QLabel>
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include "moveitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_click(MoveItem *item);

    void on_lineEdit_returnPressed();
private:
    Ui::MainWindow *ui;


    QWidget *window;

    QHBoxLayout *layout;

    QGraphicsScene *scene;
    QGraphicsScene *scene_2;

    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;

    MoveItem *item1[4];
    MoveItem *item2[3];
    MoveItem *item3[2];
    MoveItem *item4;

    MoveItem *item;

    QGraphicsTextItem *word[10];

    QGraphicsTextItem *word1[10];

    QGraphicsTextItem *left[10];

    QGraphicsTextItem *left1[10];

    QPushButton *start_button;
    QGraphicsProxyWidget *proxy_widget;

    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    std::map<MoveItem *, std::pair<QGraphicsLineItem *, QGraphicsLineItem *> > lines;

};

#endif // MAINWINDOW_H
