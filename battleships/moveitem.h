#ifndef MOVEITEM_H
#define MOVEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QCursor>


class MoveItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveItem(int x, int which_scene = 1, QObject *parent = 0);
    ~MoveItem();

    bool isLocked();

    bool marked;

signals:
    void locked();
    void clicked();

private:
    int which;
    qreal angle;
    bool in_pos;
    bool is_locked;

    int which_scene;

    QRegion boundingRegion(const QTransform &itemToDeviceTransform);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void lock();
    void x_mark();
};

#endif // MOVEITEM_H
