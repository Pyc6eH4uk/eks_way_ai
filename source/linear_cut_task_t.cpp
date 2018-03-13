//
// Created by pyc6eh4uk on 09.03.18.
//

#include "linear_cut_task_t.h"

linear_cut_task_t::linear_cut_task_t(const std::vector<linear_cut_task_t::package_t> &packages,
                                     const std::vector<linear_cut_task_t::package_t> &patterns) {
    this->packages = packages;
    this->patterns = patterns;
}

std::vector<int> linear_cut_task_t::find_linear_cut(int index, const row_t &v) {
    auto length = packages[index].length;
    std::vector<int> ans(length + 1);
    row_t target(length + 1);
    for (int i = 0; i <= length; i++) {
        ans[i] = 0;
        target[i] = 0;
        for (int j = 0; j < patterns.size(); j++) {
            auto l = patterns[j].length;
            if (l <= i && (target[i] < target[i - l] + (-1) * v[j])) {
                target[i] = target[i - l] + (-1) * v[j];
                ans[i] = j + 1;
            }
        }
    }

    std::vector<int> result(patterns.size(), 0);
    int y = length;
    while (ans[y] > 0) {
        result[ans[y] - 1]++;
        y -= result[ans[y] - 1];
    }
    return result;
}

double linear_cut_task_t::get_cost(int index) const {
    return 1;
}

double linear_cut_task_t::get_equality(int index) const {
    return 0;
}

row_t linear_cut_task_t::get_column(int index) const {
    row_t column;
    return column;
}

int linear_cut_task_t::variable_size() const {
    return 0;
}

int linear_cut_task_t::original_variable_size() const {
    return 0;
}

int linear_cut_task_t::basis_size() const {
    return 0;
}

std::vector<std::vector<int>>
linear_cut_task_t::get_all_cuts(int length, const std::vector<linear_cut_task_t::package_t> &patterns) {
    linear_cut_generator_t generator(length, patterns);
    return generator.result();
}

simplex_task_t*
linear_cut_task_t::make_standart_simplex_task(const std::vector<linear_cut_task_t::package_t> &packages,
                                              const std::vector<linear_cut_task_t::package_t> &patterns) {
    std::vector<simplex_method_unequality_t> unequalities;
    std::vector<row_t> columns;
    for (int i = 0; i < packages.size(); i++) {
        auto cuts = linear_cut_task_t::get_all_cuts(packages[i].length, patterns);
        for (auto cut : cuts) {
            row_t column;
            for (auto j : cut)
                column.push_back(j);
            for (int j = 0; j < packages.size(); j++)
                column.push_back(i == j);
            columns.push_back(column);
        }
    }
    std::vector<row_t> rows(patterns.size() + packages.size());
    for (int i = 0; i < rows.size(); i++) {
        rows[i] = row_t(columns.size());
    }
    for (int i = 0; i < columns.size(); i++) {
        for (int j = 0; j < rows.size(); j++) {
            rows[j][i] = columns[i][j];
        }
    }
    for (int i = 0; i < patterns.size(); i++) {
        unequalities.emplace_back(rows[i], patterns[i].low_size, simplex_method_unequality_t::type_t::GREATER);
        unequalities.emplace_back(rows[i], patterns[i].high_size, simplex_method_unequality_t::type_t::LESS);
    }
    for (int i = (int) patterns.size(), j = 0; i < rows.size(); i++, j++) {
        unequalities.emplace_back(rows[i], packages[j].low_size, simplex_method_unequality_t::type_t::GREATER);
        unequalities.emplace_back(rows[i], packages[j].high_size, simplex_method_unequality_t::type_t::LESS);
    }
    row_t cost;
    for (int i = 0; i < columns.size(); i++) {
        cost.push_back(-1);
    }
    return new simplex_task_t(cost, unequalities);
}

linear_cut_generator_t::linear_cut_generator_t(int length, const std::vector<linear_cut_task_t::package_t> &patterns) {
    _length = length;
    _patterns = patterns;

    f(length, 0, {});
}

void linear_cut_generator_t::f(int length, int last, std::vector<int> current) {
    if (length >= 0 && !current.empty()) {
        _result.push_back(current);
    }
    if (length <= 0)
        return;

    for (int i = last; i < _patterns.size(); i++) {
        current.push_back(i);
        f(length - _patterns[i].length, i, current);
        current.pop_back();
    }
}

std::vector<std::vector<int>> linear_cut_generator_t::result() {
    std::vector<std::vector<int>> res;
    for (auto cut : _result) {
        std::vector<int> cut_count(_patterns.size(), 0);
        for (int i : cut)
            cut_count[i]++;
        res.push_back(cut_count);
    }
    return res;
}
