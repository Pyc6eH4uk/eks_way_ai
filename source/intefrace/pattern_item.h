//
// Created by pyc6eh4uk on 08.05.18.
//

#ifndef EKS_WAY_AI_PATTERN_ITEM_H
#define EKS_WAY_AI_PATTERN_ITEM_H

#include <QtWidgets/QGraphicsItem>

class PatternItem : public QGraphicsItem
{
public:

    PatternItem(int x, int y, int w = 110, int h = 70);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int x;
    int y;
    int w;
    int h;
    QColor color;
    QVector<QPointF> stuff;
};


#endif //EKS_WAY_AI_PATTERN_ITEM_H
