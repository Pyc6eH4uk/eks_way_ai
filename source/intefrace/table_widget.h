//
// Created by pyc6eh4uk on 06.05.18.
//
#ifndef EKS_WAY_AI_WINDOW_CUT_H
#define EKS_WAY_AI_WINDOW_CUT_H

#include <QtWidgets/QWidget>
#include <QPainter>


//class QPaintEvent;

class table_widget : public QWidget {
    Q_OBJECT
public:
    table_widget(QWidget * parent = 0);

    ~table_widget();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif //EKS_WAY_AI_TABLE_WIDGET_H
