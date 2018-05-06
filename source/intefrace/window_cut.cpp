//
// Created by pyc6eh4uk on 29.03.18.
//

#include "window_cut.h"
#include "table_widget.h"
#include <QMenuBar>
#include <QDebug>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <source/linear_cut_task_t.h>
#include <source/linear_cut_debuger_t.h>
#include <QPainter>

window_cut::window_cut(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Cutting helper");

    _tableWidget = new table_widget(this);
//    _tableWidget = new table_widget(this);
    _file_menu = new QMenu(tr("Файл"));
    _open_action = new QAction(tr("Открыть"));
    _close_action = new QAction(tr("Закрыть"));
    _file_menu->addAction(_open_action);
    _file_menu->addAction(_close_action);
    _value_label = new QLabel(tr("Объём кроя: 0"));

    connect(_open_action, SIGNAL(triggered()), this, SLOT(open()));
    connect(_close_action, SIGNAL(triggered()), this, SLOT(close()));

    _central_widget = new QWidget();
    _tab_cutting_table = new QVBoxLayout();
    _tab_widget = new QTabWidget();

    _cutting_table = new QTableWidget();
    _cutting_table->setColumnCount(2);

    auto page2 = new QWidget();

    _tab_widget->addTab(_cutting_table, tr("Раскрой"));
    _tab_widget->addTab(page2, tr("Рисунок"));

    _vertical_layout_left_table = new QVBoxLayout();

    auto package_label = new QLabel(tr("Брёвна"));
    auto pattern_label = new QLabel(tr("Заготовки"));

    auto column_packages_names = QStringList();
    column_packages_names << tr("Длина") << tr("Количество");

    auto column_patterns_names = QStringList();
    column_patterns_names << tr("Длина") << tr("Минимум") << tr("Максимум");

    _vertical_layout_right_table = new QVBoxLayout();
    _horizontal_layout = new QHBoxLayout();
    _packages_table = new QTableWidget();
    _packages_table->setColumnCount(2);
    _packages_table->setHorizontalHeaderLabels(column_packages_names);
//    _packages_table->setMaximumHeight(300);

    _patterns_table = new QTableWidget();
    _patterns_table->setColumnCount(3);
    _patterns_table->setHorizontalHeaderLabels(column_patterns_names);

//    _patterns_table->setMaximumHeight(300);
//    _vertical_layout_left_table->addWidget(package_label);
//    _vertical_layout_left_table->addWidget(_packages_table);
//    _vertical_layout_right_table->addWidget(pattern_label);
//    _vertical_layout_right_table->addWidget(_patterns_table);

    _vertical_layout_right_table->addWidget(_tableWidget);

    _horizontal_layout->addLayout(_vertical_layout_left_table);
    _horizontal_layout->addLayout(_vertical_layout_right_table);

    _tab_cutting_table->addLayout(_horizontal_layout);
    _tab_cutting_table->addWidget(_tab_widget);
    _tab_cutting_table->addWidget(_value_label);
    _central_widget->setLayout(_tab_cutting_table);


    menuBar()->addMenu(_file_menu);
    setCentralWidget(_central_widget);
}

window_cut::~window_cut() {

}

QVBoxLayout *window_cut::get_vertical_layout_left_table() const {
    return _vertical_layout_left_table;
}

void window_cut::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open input data"), "",
                                                    tr("Input data (*.txt)"));

    qDebug() << fileName;
    disconnect(_packages_table, SIGNAL(cellChanged(int, int)), 0, 0);
    disconnect(_patterns_table, SIGNAL(cellChanged(int, int)), 0, 0);

    clear();

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        QTextStream in(&file);
        std::vector<linear_cut_task_t::package_t> packages;
        std::vector<linear_cut_task_t::package_t> patterns;

        int m, n, piece, length, count, low_length, high_length;
        in >> m;
        in >> n;
        in >> piece;

        for (int i = 0; i < m; i++) {
            in >> length;
            in >> low_length;
            in >> high_length;
            patterns.push_back({length, low_length, high_length});

            _patterns_table->insertRow(_patterns_table->rowCount());
            _patterns_table->setItem(_patterns_table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(length)));
            _patterns_table->setItem(_patterns_table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(low_length)));
            _patterns_table->setItem(_patterns_table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(high_length)));
        }

        for (int i = 0; i < n; i++) {
            in >> length;
            in >> count;
            packages.push_back({length, 0, count});

            _packages_table->insertRow(_packages_table->rowCount());
            _packages_table->setItem(_packages_table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(length)));
            _packages_table->setItem(_packages_table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(count)));
        }
    }

    connect(_packages_table, SIGNAL(cellChanged(int, int)), this, SLOT(onChange(int, int)));
    connect(_patterns_table, SIGNAL(cellChanged(int, int)), this, SLOT(onChange(int, int)));

    onChange(0, 0);
}

void window_cut::onChange(int row, int column) {
    std::vector<linear_cut_task_t::package_t> packages;
    std::vector<linear_cut_task_t::package_t> patterns;

    for (int i = 0; i < _packages_table->rowCount(); i++) {
        auto length = _packages_table->item(i, 0)->text().toInt();
        auto count = _packages_table->item(i, 1)->text().toInt();
        packages.push_back({length, 0, count});
    }

    for (int i = 0; i < _patterns_table->rowCount(); i++) {
        qDebug() << _patterns_table->item(i, 0)->text() << _patterns_table->item(i, 1)->text() << _patterns_table->item(i, 2)->text();
        auto length = _patterns_table->item(i, 0)->text().toInt();
        auto min = _patterns_table->item(i, 1)->text().toInt();
        auto max = _patterns_table->item(i, 2)->text().toInt();
        patterns.push_back({length, min, max});
    }

    auto task = new linear_cut_task_t(packages, patterns);
    auto simplex_method = new simplex_method_t(task);
    auto debuger = new linear_cut_debuger_t();
    simplex_method->solve(debuger);

    real_t value = 0;
    for (int i = 0; i < task->basis_size(); i++) {
        auto x = simplex_method->get_x(i);
        value += x * task->get_cost(simplex_method->get_basis(i));
    }

    _value_label->setText(tr("Объём кроя: ") + QString::number(- value));
    _cutting_table->setColumnCount(2 + task->get_patterns().size());

    _cutting_table->clear();
    _cutting_table->setRowCount(0);

    for (int i = 0; i < task->basis_size(); i++) {
        auto column = simplex_method->get_column(i);
        auto x = simplex_method->get_x(i);
        if (simplex_method->get_basis(i) >= task->get_packages().size())
            continue;
        if (column.empty())
            continue;
        auto package_id = simplex_method->get_basis(i);
        _cutting_table->insertRow(_cutting_table->rowCount());
        _cutting_table->setItem(_cutting_table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(package_id + 1)));
        _cutting_table->setItem(_cutting_table->rowCount() - 1, 1, new QTableWidgetItem(QString::number((int) x)));
        for (int j = 0; j < task->get_patterns().size(); j++) {
            _cutting_table->setItem(_cutting_table->rowCount() - 1, j + 2, new QTableWidgetItem(QString::number((int) column[j])));
        }
    }
}

void window_cut::clear() {
    _packages_table->clear();
    _packages_table->setRowCount(0);

    _patterns_table->clear();
    _patterns_table->setRowCount(0);
}

void window_cut::close() {
    QWidget::close();
}
