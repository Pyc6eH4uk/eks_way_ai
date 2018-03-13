#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"
#include "source/linear_cut_task_t.h"

int main() {
    std::vector<linear_cut_task_t::package_t> packages;
    std::vector<linear_cut_task_t::package_t> patterns;

    /*
    patterns.push_back({2, 50, 65});
    patterns.push_back({3, 50, 65});

    packages.push_back({6, 0, 19});
    packages.push_back({7, 0, 37});
    */

    packages.push_back({56, 0, 19});
    packages.push_back({59, 0, 19});
    packages.push_back({63, 0, 37});

    patterns.push_back({6, 20, 38});
    patterns.push_back({9, 40, 47});
    patterns.push_back({12, 30, 32});
    patterns.push_back({13, 50, 52});
    patterns.push_back({21, 30, 46});
    patterns.push_back({27, 50, 65});

    auto task = linear_cut_task_t::make_standart_simplex_task(packages, patterns);
    auto simplex_method = new simplex_method_t(task);

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