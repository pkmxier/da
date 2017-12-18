#include "QBoxLayout"
#include "mainwindow.h"
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
#include <QSignalMapper>
#include <string>
#include "moveitem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->lineEdit->selectAll();

    window = new QWidget;

    layout = new QHBoxLayout;

    scene = new QGraphicsScene();
    scene_2 = new QGraphicsScene();

    graphicsView = new QGraphicsView();
    graphicsView_2 = new QGraphicsView();

    layout->addWidget(graphicsView);
    layout->addWidget(graphicsView_2);

    graphicsView->setScene(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene->setSceneRect(0, 0, 900, 1000);


    graphicsView_2->setScene(scene_2);
    graphicsView_2->setRenderHint(QPainter::Antialiasing);
    graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_2->setSceneRect(scene->sceneRect());

    for (int i = 0; i < 4; ++i) {
        item1[i] = new MoveItem(1);
        item1[i]->setPos(700 + i * 60, 50);
        scene->addItem(item1[i]);
    }
    for (int i = 0; i < 3; ++i) {
        item2[i] = new MoveItem(2);
        item2[i]->setPos(700 + i * 60, 150);
        scene->addItem(item2[i]);
    }
    for (int i = 0; i < 2; ++i) {
        item3[i] = new MoveItem(3);
        item3[i]->setPos(700 + i * 60, 310);
        scene->addItem(item3[i]);
    }
    item4 = new MoveItem(4);
    item4->setPos(700, 530);
    scene->addItem(item4);

    item = new MoveItem(1, 2);
    item->setPos(10, 30);
    scene_2->addItem(item);

    for (int i = 0; i <= 10; ++i) {
        scene->addLine(40 + i * 60, 40, 40 + i * 60, 640);
        scene->addLine(40, 40 + i * 60, 640, 40 + i * 60);

        scene_2->addLine(40 + i * 60, 40, 40 + i * 60, 640);
        scene_2->addLine(40, 40 + i * 60, 640, 40 + i * 60);
    }

    word[0] = scene_2->addText("A");
    word[1] = scene_2->addText("Б");
    word[2] = scene_2->addText("В");
    word[3] = scene_2->addText("Г");
    word[4] = scene_2->addText("Д");
    word[5] = scene_2->addText("Е");
    word[6] = scene_2->addText("Ж");
    word[7] = scene_2->addText("З");
    word[8] = scene_2->addText("И");
    word[9] = scene_2->addText("К");

    word1[0] = scene_2->addText("1");
    word1[1] = scene_2->addText("2");
    word1[2] = scene_2->addText("3");
    word1[3] = scene_2->addText("4");
    word1[4] = scene_2->addText("5");
    word1[5] = scene_2->addText("6");
    word1[6] = scene_2->addText("7");
    word1[7] = scene_2->addText("8");
    word1[8] = scene_2->addText("9");
    word1[9] = scene_2->addText("10");

    left[0] = scene->addText("A");
    left[1] = scene->addText("Б");
    left[2] = scene->addText("В");
    left[3] = scene->addText("Г");
    left[4] = scene->addText("Д");
    left[5] = scene->addText("Е");
    left[6] = scene->addText("Ж");
    left[7] = scene->addText("З");
    left[8] = scene->addText("И");
    left[9] = scene->addText("К");

    left1[0] = scene->addText("1");
    left1[1] = scene->addText("2");
    left1[2] = scene->addText("3");
    left1[3] = scene->addText("4");
    left1[4] = scene->addText("5");
    left1[5] = scene->addText("6");
    left1[6] = scene->addText("7");
    left1[7] = scene->addText("8");
    left1[8] = scene->addText("9");
    left1[9] = scene->addText("10");

    for (int i = 0; i < 10; ++i) {
        left[i]->setPos(62.5 + i * 60, 10);
        left1[i]->setPos(10, 60 + i * 60);

        word[i]->setPos(62.5 + i * 60, 10);
        word1[i]->setPos(10, 60 + i * 60);
    }

    start_button = new QPushButton("Start");
    QObject::connect(start_button, SIGNAL(clicked()), item1[0], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item1[1], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item1[2], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item1[3], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item2[0], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item2[1], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item2[2], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item3[0], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item3[1], SLOT(lock()));
    QObject::connect(start_button, SIGNAL(clicked()), item4, SLOT(lock()));


    for (int i = 0; i < 4; ++i) {
        QObject::connect(item1[i], &MoveItem::clicked, this, [i, this] {
            on_click(item1[i]);
        });

        if (i  < 3) {
            QObject::connect(item2[i], &MoveItem::clicked, this, [i, this] {
                on_click(item2[i]);
            });
        }

        if (i < 2) {
            QObject::connect(item3[i], &MoveItem::clicked, this, [i, this] {
                on_click(item3[i]);
            });
        }
    }

    QObject::connect(item4, &MoveItem::clicked, this, [this] {
        on_click(item4);
    });

    proxy_widget = scene->addWidget(start_button);
    proxy_widget->setPos(700, 700);
    window->setLayout(layout);
    layout-> setSizeConstraint ( QLayout :: SetFixedSize ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString username = ui->lineEdit->text();

    this->close();

    window->show();
}

void MainWindow::on_click(MoveItem *item) {
    if (!item->marked) {
        lines[item] = std::make_pair(new QGraphicsLineItem(item->pos().x() - 30, item->pos().y() - 30, item->pos().x() + 30, item->pos().y() + 30),
                                     new QGraphicsLineItem(item->pos().x() - 30, item->pos().y() + 30, item->pos().x() + 30, item->pos().y() - 30));
        scene->addItem(lines[item].first);
        scene->addItem(lines[item].second);
        item->marked = true;
    } else {
        scene->removeItem(lines[item].first);
        scene->removeItem(lines[item].second);
        delete lines[item].first;
        delete lines[item].second;
        lines.erase(item);
        item->marked = false;
    }

}

void MainWindow::on_lineEdit_returnPressed()
{
    this->ui->pushButton->click();
}
