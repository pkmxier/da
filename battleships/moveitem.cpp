#include "moveitem.h"
#include <QLineF>
#include <iostream>
#include <QImage>

MoveItem::MoveItem(int x, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;
    which = x;
    in_pos = false;
    is_locked = false;
}

MoveItem::~MoveItem()
{

}

void MoveItem::lock()
{
    is_locked = true;
    emit locked();
}

void MoveItem::x_mark() {
    this->setRotation(45);
}

QRectF MoveItem::boundingRect() const
{
    if (which == 1) {
        return QRectF (-30,-30,60,60);
    } else if (which == 2) {
        return QRectF (-30,-60,60,120);
    } else if (which == 3) {
        return QRectF (-30,-90,60,180);
    } else if (which == 4) {
        return QRectF (-30,-120,60,240);
    }
}

void MoveItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);

    QImage image;
    image.load("/home/pkmixer/image.png");
    QImage image1;
    image1.load("/home/pkmixer/image1");
    QImage image2;
    image2.load("/home/pkmixer/image2.png");
    QImage image3;
    image3.load("/home/pkmixer/image3.png");


    if (which == 1) {
        painter->drawImage(-30, -30, image);
    } else if (which == 2) {
        painter->drawImage(-30, -60, image1);
    } else if (which == 3) {
        painter->drawImage(-30, -90, image2);
    } else if (which == 4) {
        painter->drawImage(-30, -120, image3);
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Устанавливаем позицию графического элемента
     * в графической сцене, транслировав координаты
     * курсора внутри графического элемента
     * в координатную систему графической сцены
     * */

    if (!is_locked)
    this->setPos(mapToScene(event->pos()));
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* При нажатии мышью на графический элемент
     * заменяем курсор на руку, которая держит этот элемента
     * */
    if (!is_locked) {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    }
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* При отпускании мышью элемента
     * заменяем на обычный курсор стрелку
     * */
    if (!is_locked) {
        this->setCursor(QCursor(Qt::ArrowCursor));
        Q_UNUSED(event);

        QPointF matrix[10][10];
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                matrix[i][j] = {100 + i * 60, 100 + j * 60};

                QLineF *line = new QLineF(matrix[i][j], this->cursor().pos());

                if (which == 2 || which == 4) {
                    if (line->length() < 30) {
                        if (angle == 0) {
                            if (matrix[i][j].y() - this->cursor().pos().y() > 0) {
                                this->setPos(matrix[i][j].x() - 30, matrix[i][j].y() - 60);
                            } else {
                                this->setPos(matrix[i][j].x() - 30, matrix[i][j].y());
                            }
                        } else {
                            if (matrix[i][j].x() - this->cursor().pos().x() > 0) {
                                this->setPos(matrix[i][j].x() - 60, matrix[i][j].y() - 30);
                            } else {
                                this->setPos(matrix[i][j].x(), matrix[i][j].y() - 30);
                            }
                        }

                        in_pos = true;
                    }
                } else if (line->length() < 30) {
                    this->setPos(matrix[i][j].x() - 30, matrix[i][j].y() - 30);
                    in_pos = true;
                    return;
                }
            }
        }

        in_pos = false;
    }
}

void MoveItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_locked) {
        if (this->angle == 0) {
            this->angle = 90;
            this->setRotation(angle);
        } else {
            this->angle = 0;
            this->setRotation(0);
        }

        if (in_pos) {
            //some code?..
        }
    }
}
