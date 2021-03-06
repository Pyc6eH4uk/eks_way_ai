//
// Created by pyc6eh4uk on 29.03.18.
//

#include "window_cut.h"
#include "pattern_item.h"
#include <QMenuBar>
#include <QDebug>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <source/linear_cut_task_t.h>
#include <source/linear_cut_debuger_t.h>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSplitter>


window_cut::window_cut(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Cutting helper");

    _file_menu = new QMenu(tr("Файл"));
    _open_action = new QAction(tr("Открыть"));
    _close_action = new QAction(tr("Закрыть"));
    _file_menu->addAction(_open_action);
    _file_menu->addAction(_close_action);
    _value_label = new QLabel(tr("Объём кроя: 0"));
    _pattern_view = new View("Результат:");
    _scene = new QGraphicsScene(this);
    _pattern_view->view()->setScene(_scene);

    connect(_open_action, SIGNAL(triggered()), this, SLOT(open()));
    connect(_close_action, SIGNAL(triggered()), this, SLOT(close()));

    _central_widget = new QWidget();
    _tab_cutting_table = new QVBoxLayout();
    _tab_widget = new QTabWidget();
    _cutting_table = new QTableWidget();
//    _cutting_table->setColumnCount(2);


    auto page2 = new QWidget();

    _tab_widget->addTab(_cutting_table, tr("Раскрой"));
    _tab_widget->addTab(_pattern_view, tr("Рисунок"));

    _vertical_layout_left_table = new QVBoxLayout();

    auto package_label = new QLabel(tr("Брус"));
    auto pattern_label = new QLabel(tr("Заготовки"));

    auto column_packages_names = QStringList();
    column_packages_names << tr("Длина") << tr("Количество") << tr("Расход") << tr("Остаток");

    auto column_patterns_names = QStringList();
    column_patterns_names << tr("Длина") << tr("Минимум") << tr("Максимум") << tr("Расход") << tr("Остаток");

    _vertical_layout_right_table = new QVBoxLayout();
    _horizontal_layout = new QHBoxLayout();
    _packages_table = new QTableWidget();
    _packages_table->setColumnCount(4);
    _packages_table->setHorizontalHeaderLabels(column_packages_names);
//    _packages_table->setMaximumHeight(300);

    _patterns_table = new QTableWidget();
    _patterns_table->setColumnCount(5);
    _patterns_table->setHorizontalHeaderLabels(column_patterns_names);

    _vertical_layout_left_table->addWidget(package_label);
    _vertical_layout_left_table->addWidget(_packages_table);
    _vertical_layout_right_table->addWidget(pattern_label);
    _vertical_layout_right_table->addWidget(_patterns_table);


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


void window_cut::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open input data"), "",
                                                    tr("Input data (*.txt)"));

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
            _patterns_table->setItem(_patterns_table->rowCount() - 1, 3, new QTableWidgetItem(QString::number(0)));
            _patterns_table->setItem(_patterns_table->rowCount() - 1, 4, new QTableWidgetItem(QString::number(0)));
        }

        for (int i = 0; i < n; i++) {
            in >> length;
            in >> count;
            packages.push_back({length, 0, count});

            _packages_table->insertRow(_packages_table->rowCount());
            _packages_table->setItem(_packages_table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(length)));
            _packages_table->setItem(_packages_table->rowCount() - 1, 1, new QTableWidgetItem(QString::number(count)));
            _packages_table->setItem(_packages_table->rowCount() - 1, 2, new QTableWidgetItem(QString::number(0)));
            _packages_table->setItem(_packages_table->rowCount() - 1, 3, new QTableWidgetItem(QString::number(0)));
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
        _packages_table->item(i, 2)->text().toInt();
        _packages_table->item(i, 3)->text().toInt();
        packages.push_back({length, 0, count});
    }

    for (int i = 0; i < _patterns_table->rowCount(); i++) {
//        qDebug() << _patterns_table->item(i, 0)->text() << _patterns_table->item(i, 1)->text() << _patterns_table->item(i, 2)->text();
        auto length = _patterns_table->item(i, 0)->text().toInt();
        auto min = _patterns_table->item(i, 1)->text().toInt();
        auto max = _patterns_table->item(i, 2)->text().toInt();
        _patterns_table->item(i, 3)->text().toInt();
        _patterns_table->item(i, 4)->text().toInt();
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
    _cutting_table->setColumnCount(2 + (int) task->get_patterns().size());

    _cutting_table->clear();
    _cutting_table->setRowCount(0);
    _scene->clear();

    QStringList list;
    list.push_back(tr("Тип бруса"));
    list.push_back(tr("Кратность кроя"));
    for (int i = 0; i < task->get_patterns().size(); i++) {
        list.push_back(QString::number(i + 1));
    }
    _cutting_table->setHorizontalHeaderLabels(list);
    _cutting_table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    _cutting_table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    int useful_packages = 0;

    int min_width = INT_MAX;
    std::map<int, int> patterns_map;
    for (int i = 0; i < task->get_patterns().size(); i++) {
        min_width = std::min(min_width, task->get_patterns()[i].length);
        patterns_map.insert(std::pair<int, int>(task->get_patterns()[i].length, 0));
    }

    std::vector<std::vector <int >> used_packages(packages.size(), std::vector<int>(task->basis_size()));
    std::vector<std::vector <int >> used_patterns(patterns.size(), std::vector<int>(1));

    for (int i = 0; i < task->basis_size(); i++) {
        int sum = 0;
        auto column = simplex_method->get_column(i);
        auto x = simplex_method->get_x(i);
        if (int(x) == 0)
            continue;
        if (simplex_method->get_basis(i) >= task->get_packages().size())
            continue;
        if (column.empty())
            continue;
        std::vector<linear_cut_task_t::package_t> patterns_to_draw;
        auto package_id = simplex_method->get_basis(i);
        _cutting_table->insertRow(_cutting_table->rowCount());
        _cutting_table->setItem(_cutting_table->rowCount() - 1, 0, new QTableWidgetItem(QString::number(package_id + 1) + "(" +
                                                                                        QString::number(packages[package_id].length) + ")"));
        _cutting_table->setItem(_cutting_table->rowCount() - 1, 1, new QTableWidgetItem(QString::number((int) x)));
        used_packages[package_id][i] = (int) x;

        for (int j = 0; j < task->get_patterns().size(); j++) {
            sum += (int) x;
            _cutting_table->setItem(_cutting_table->rowCount() - 1, j + 2, new QTableWidgetItem(QString::number((int) column[j])));
            int count = (int) column[j];
            if (count > 0) {
                patterns_to_draw.push_back(task->get_patterns()[j]);
                patterns_to_draw.back().low_size = count;
            }
        }

        int pos_x = 0;
        QGraphicsTextItem *textItem = new QGraphicsTextItem(tr("Брус типа ") + QString::number(package_id + 1) +
                                                            tr(" кроится ") + QString::number((int)x) + tr(" раз"));
        textItem->setFont(QFont("arial", 3));
        textItem->setPos(QPointF(-80, (useful_packages - 0.5f) * (min_width + min_width / 5)));
        _scene->addItem(textItem);

        for (int j = 0; j < patterns_to_draw.size(); j++) {
            for (int k = 0; k < patterns_to_draw[j].low_size; k++) {
                QGraphicsItem *pattern_item = new PatternItem(pos_x, useful_packages * (min_width + min_width / 5), patterns_to_draw[j].length, min_width);
                patterns_map[patterns_to_draw[j].length]++;
                pattern_item->setPos(QPointF(pos_x, useful_packages * (min_width + min_width / 5)));
                pattern_item->setZValue(0);
                _scene->addItem(pattern_item);
                pos_x += patterns_to_draw[j].length;
            }
        }
        useful_packages += 1;
    }

    for (int i = 0; i < task->get_packages().size(); i++) {
        int sum = 0;
        for (int j = 0; j < task->basis_size(); j++) {
            sum += used_packages[i][j];
        }
        _packages_table->item(i, 2)->setText(QString::number(sum));
        _packages_table->item(i, 3)->setText(QString::number(packages[i].high_size - sum));
    }

    for (int i = 0; i < task->get_patterns().size(); i++) {
        _patterns_table->item(i, 3)->setText(QString::number(patterns_map[patterns[i].length]));
        _patterns_table->item(i, 4)->setText(QString::number(patterns[i].low_size - patterns_map[patterns[i].length]));
    }
}


void window_cut::clear() {
    auto column_packages_names = QStringList();
    column_packages_names << tr("Длина") << tr("Количество") << tr("Расход") << tr("Остаток");

    _packages_table->clear();
    _packages_table->setRowCount(0);
    _packages_table->setHorizontalHeaderLabels(column_packages_names);

    auto column_patterns_names = QStringList();
    column_patterns_names << tr("Длина") << tr("Минимум") << tr("Максимум") << tr("Расход") << tr("Остаток");

    _patterns_table->clear();
    _patterns_table->setRowCount(0);
    _patterns_table->setHorizontalHeaderLabels(column_patterns_names);
}


void window_cut::close() {
    QWidget::close();
}
