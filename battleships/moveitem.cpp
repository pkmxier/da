#include "moveitem.h"
#include <QLineF>
#include <iostream>
#include <QPainter>
#include <QImage>

MoveItem::MoveItem(int x, int which_scene, int angle, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    this->angle = angle;
    which = x;
    is_locked = false;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            matrix[i][j] = {100 + i * 60, 100 + j * 60};
            marked[i][j] = false;
        }
    }

    in_position = false;

    this->which_scene = which_scene;

    this->setRotation(this->angle);
}

MoveItem::~MoveItem()
{

}

bool MoveItem::isLocked() {
    return is_locked;
}

qreal MoveItem::getAngle() {
    return this->angle;
}

std::pair<int, int> MoveItem::which_point() {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << matrix[i][j].x() << " " << matrix[i][j].y() << std::endl;
            std::cout << pos().x() << " " << pos().y() << std::endl << std::endl;
            if (matrix[i][j].x() == this->pos().x() + 30 && matrix[i][j].y() == this->pos().y() + 30) {
                return std::make_pair(matrix[i][j].x(), matrix[i][j].y());
            }
        }
    }
}

int * MoveItem::build_ships_map() {
    int *ships_map = new int[100];
    std::pair<int, int> cur;
    if (in_position) {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                ships_map[10 * i + j] = 0;

                if (matrix[i][j].x() == this->pos().x() + 30 && matrix[i][j].y() == this->pos().y() + 30 ||
                    matrix[i][j].x() == this->pos().x() + 30 && matrix[i][j].y() == this->pos().y() ||
                    matrix[i][j].x() == this->pos().x() && matrix[i][j].y() == this->pos().y() + 30) {
                    cur = std::make_pair(i, j);
                }
            }
        }

        if (which == 1) {
            ships_map[10 * cur.first + cur.second] -= 1;
        } else if (which == 2) {
            if (angle == 0) {
                ships_map[10 * cur.first + cur.second] -= 1;
                ships_map[10 * (cur.first + 1) + cur.second] -= 1;
            } else {
                ships_map[10 * cur.first + cur.second] -= 1;
                ships_map[10 * cur.first + cur.second + 1] -= 1;
            }
        } else if (which == 3) {
            if (angle == 0) {
                ships_map[10 * (cur.first - 1) + cur.second] -= 1;
                ships_map[10 * cur.first + cur.second] -= 1;
                ships_map[10 * (cur.first + 1) + cur.second] -= 1;
            } else {
                ships_map[10 * cur.first + cur.second - 1] -= 1;
                ships_map[10 * cur.first + cur.second] -= 1;
                ships_map[10 * cur.first + cur.second + 1] -= 1;
            }
        } else {
            if (angle == 0) {
                ships_map[10 * (cur.first) + cur.second - 1] -= 1;
                ships_map[10 * (cur.first + 1) + cur.second - 1] -= 1;
                ships_map[10 * (cur.first + 2) + cur.second - 1] -= 1;
                ships_map[10 * (cur.first + 3) + cur.second - 1] -= 1;
            } else {
                ships_map[10 * cur.first + cur.second - 2] -= 1;
                ships_map[10 * cur.first + cur.second - 1] -= 1;
                ships_map[10 * cur.first + cur.second] -= 1;
                ships_map[10 * cur.first + cur.second + 1] -= 1;
            }
        }
    }
    return ships_map;
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

    //this->setRotation(this->angle);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}



void MoveItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_locked) {
        this->setPos(mapToScene(event->pos()));
    }
}

void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_locked) {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
        Q_UNUSED(event);
    } else {
        emit clicked();
    }
}

void MoveItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_locked) {
        this->setCursor(QCursor(Qt::ArrowCursor));
        Q_UNUSED(event);

        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                QPointF cur = {this->pos().x() + 30, this->pos().y() + 30};
                QLineF *line = new QLineF(matrix[i][j], cur);

                if (which == 2 || which == 4) {
                    if (line->length() < 30) {
                        if (angle == 0) {
                            if (matrix[i][j].y() - cur.y() > 0) {
                                this->setPos(matrix[i][j].x() - 30, matrix[i][j].y() - 60);
                            } else {
                                this->setPos(matrix[i][j].x() - 30, matrix[i][j].y());
                            }
                        } else {
                            if (matrix[i][j].x() - cur.x() > 0) {
                                this->setPos(matrix[i][j].x() - 60, matrix[i][j].y() - 30);
                            } else {
                                this->setPos(matrix[i][j].x(), matrix[i][j].y() - 30);
                            }
                        }

                        in_position = true;
                    }
                } else if (line->length() < 30) {
                    this->setPos(matrix[i][j].x() - 30, matrix[i][j].y() - 30);
                    in_position = true;
                }

                delete line;
            }
        }
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
    }
}
