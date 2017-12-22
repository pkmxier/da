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
#include <QTextEdit>
#include <QTcpSocket>
#include "zhelpers.hpp"
#include "moveitem.h"

struct ship {
    double x;
    double y;
    int angle;

    void operator =(ship ship_) {
        x = ship_.x;
        y = ship_.y;
        angle = ship_.angle;
    }
};

struct MessageData {
    int clientId;
    ship ships[10];
    char message[128];
    int type;
};

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
    void send_ships_map();

private:
    Ui::MainWindow *ui;

    zmq::context_t *context;
    zmq::socket_t *worker;


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

    MoveItem *i1[4];
    MoveItem *i2[3];
    MoveItem *i3[2];
    MoveItem *i4;


    QGraphicsTextItem *word[10];

    QGraphicsTextItem *word1[10];

    QGraphicsTextItem *left[10];

    QGraphicsTextItem *left1[10];

    QPushButton *start_button;
    QGraphicsProxyWidget *proxy_widget;

    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

    std::map<int, std::pair<QGraphicsLineItem *, QGraphicsLineItem *> > lines;

    std::string username;
};

#endif // MAINWINDOW_H
