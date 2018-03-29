//
// Created by pyc6eh4uk on 29.03.18.
//

#ifndef EKS_WAY_AI_WINDOW_CUT_H
#define EKS_WAY_AI_WINDOW_CUT_H


#include <QtWidgets/QMainWindow>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QLabel>

class window_cut : public QMainWindow {
    Q_OBJECT
protected:
    QMenu *_file_menu;
    QAction *_open_action;
    QAction *_close_action;
    QWidget *_central_widget;
    QHBoxLayout *_horizontal_layout;
    QVBoxLayout *_vertical_layout_left_table;
    QVBoxLayout *_vertical_layout_right_table;
    QVBoxLayout *_tab_cutting_table;
    QTableWidget *_cutting_table;
    QTableWidget *_patterns_table;
    QTableWidget *_packages_table;
    QTabWidget *_tab_widget;
    QLabel *_value_label;

public:
    window_cut();
    virtual ~window_cut();

    void clear();
private slots:
    void open();
    void close();
    void onChange(int row, int column);
};


#endif //EKS_WAY_AI_WINDOW_CUT_H
