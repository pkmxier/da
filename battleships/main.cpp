#include "mainwindow.h"
#include "QPushButton"
#include <QApplication>
#include <zmq.h>

pthread_t thread;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
