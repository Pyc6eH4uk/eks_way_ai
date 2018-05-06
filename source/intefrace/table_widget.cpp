//
// Created by pyc6eh4uk on 06.05.18.
//

#include <QtWidgets/QWidget>
#include "table_widget.h"

table_widget::table_widget(QWidget *parent) : QWidget(parent) {}

void table_widget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.drawEllipse(100, 50, 150, 150);
}