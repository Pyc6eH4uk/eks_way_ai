#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"
#include "source/linear_cut_task_t.h"

int main() {
    std::vector<linear_cut_task_t::package_t> packages;
    std::vector<linear_cut_task_t::package_t> patterns;

    packages.push_back({56, 0, 19});
    packages.push_back({59, 0, 19});
    packages.push_back({63, 0, 37});

    patterns.push_back({6, 20, 38});
    patterns.push_back({9, 40, 47});
    patterns.push_back({12, 30, 32});
    patterns.push_back({13, 50, 52});
    patterns.push_back({21, 30, 46});
    patterns.push_back({27, 50, 65});

    auto task = new linear_cut_task_t(packages, patterns);
    //auto task = linear_cut_task_t::make_standart_simplex_task(packages, patterns);

    auto simplex_method = new simplex_method_t(task);
/*
    double t[128][128];
    for (int i = 0; i < task->variable_size(); i++) {
        row_t costs(task->get_patterns().size(), -1);
        auto column = task->get_column(i, costs);
        for (int j = 0; j < column.size(); j++) {
            t[j][i] = column[j];
        }
    }
    for (int i = 0; i < task->basis_size(); i++) {
        for (int j = 0; j < task->variable_size(); j++) {
            std::cout << std::setw(4) << t[i][j] << " ";
        }
        std::cout << std::setw(4) << task->get_equality(i);
        std::cout << std::endl;
    }
*/
    task->print_cost();
    task->print_equality();

    real_t value;
    row_t solution;
    std::vector<int> basis;
    if (simplex_method->get_solution(solution, basis, value)) {
        std::cout << "value: " << - value << std::endl;
        std::cout << "solution:" << std::endl;
        for (auto x : solution) {
            std::cout << std::setw(4) << x << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }


    return 0;
}