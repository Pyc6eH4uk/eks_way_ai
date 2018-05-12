//
// Created by pyc6eh4uk on 08.05.18.
//

#include "pattern_item.h"

#include <QtWidgets>

PatternItem::PatternItem(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    setZValue((x + y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF PatternItem::boundingRect() const
{
    return QRectF(0, 0, w, h);
}

QPainterPath PatternItem::shape() const
{
    QPainterPath path;
    path.addRect(0, 0, w, h);
    return path;
}

void PatternItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    QLinearGradient gradient;
    gradient.setStart(0, 0);
    gradient.setFinalStop(0, h);
    gradient.setColorAt(0, QColor(61, 37, 15, 255));
    gradient.setColorAt(1, QColor(101, 67, 33, 255));

    //painter->setBrush(QColor(101, 67, 33, 255));
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawRect(QRect(h / 2, 0, w - h, h));

    //painter->setBrush(QColor(101, 67, 33, 255));
    painter->setBrush(QBrush(gradient));
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(QRect(w - h, 0, h, h));

    painter->setBrush(QColor(181, 120, 60, 255));
    painter->setPen(QPen(Qt::black, 0.01f, Qt::SolidLine, Qt::FlatCap));
    painter->drawEllipse(QRect(0, 0, h, h));

    painter->setBrush(QColor(0, 0, 255, 255));
    painter->setFont(QFont("arial", 2));
    QString txt = QString::number(w);
    painter->drawText(QPointF(h / 2 - h / 4 - (txt.size() - 1) * h / 6.0, h / 2 + h / 4), txt);
}

void PatternItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void PatternItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void PatternItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}