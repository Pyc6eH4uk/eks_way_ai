#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"
#include "source/linear_cut_task_t.h"

int main() {
    std::vector<linear_cut_task_t::package_t> packages;
    std::vector<linear_cut_task_t::package_t> patterns;

    freopen("input", "r", stdin);

    int m, n, piece, length, count, low_length, high_length;
    std::cin >> m;
    std::cin >> n;
    std::cin >> piece;

    for (int i = 0; i < m; i++) {
        std::cin >> length;
        std::cin >> low_length;
        std::cin >> high_length;
        patterns.push_back({length, low_length, high_length});
    }

    for (int i = 0; i < n; i++) {
        std::cin >> length;
        std::cin >> count;
        packages.push_back({length, piece, count});
    }

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