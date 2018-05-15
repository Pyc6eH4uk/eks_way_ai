#include <iostream>
#include <vector>
#include <limits>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <source/intefrace/window_cut.h>
#include <QPainter>
#include "source/linear_cut_debuger_t.h"

int main(int argc, char** args) {
    QApplication application(argc, args);
    QApplication::setOrganizationName("Pyc6eH4uk");
    QApplication::setApplicationName("Cutting Helper");

    auto window = new window_cut();
    window->setWindowState(Qt::WindowMaximized);
    window->show();

    return application.exec();
}