#include "item.h"

Item::Item(int x, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    which = x;
}

Item::~Item()
{

}

QRectF Item::boundingRect() const
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

void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    if (which == 1) {
        painter->drawRect(-30,-30,60,60);
    } else if (which == 2) {
        painter->drawRect(-30,-60,60,120);
    } else if (which == 3) {
        painter->drawRect(-30,-90,60,180);
    } else if (which == 4) {
        painter->drawRect(-30,-120,60,240);
    }
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Item::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}
