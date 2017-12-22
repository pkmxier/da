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
    explicit MoveItem(int x, int which_scene = 1, int angle = 0, QObject *parent = 0);
    ~MoveItem();

    bool isLocked();

    bool marked[10][10];

    bool in_position;

    qreal getAngle();

    std::pair<int, int> which_point();

    int *build_ships_map();

    signals:
    void locked();
    void clicked();

private:
    int which;
    qreal angle;
    bool is_locked;

    QPointF matrix[10][10];

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
