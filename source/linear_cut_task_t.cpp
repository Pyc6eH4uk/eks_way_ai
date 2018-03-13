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
