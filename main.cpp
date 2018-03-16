#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"
#include "source/linear_cut_task_t.h"
#include "source/linear_cut_simplex_method_t.h"

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

    patterns.push_back({6, 20, 123123});
    patterns.push_back({9, 40, 123123});
    patterns.push_back({12, 30, 123123});
    patterns.push_back({13, 50, 123123});
    patterns.push_back({21, 30, 123123});
    patterns.push_back({27, 50, 123123});

    auto task = new linear_cut_task_t(packages, patterns);
    auto simplex_method = new linear_cut_simplex_method_t(task);

    task->print_cost();
    task->print_equality();

    real_t value;
    row_t solution;
    std::vector<int> basis;
    if (simplex_method->find_solution(solution, basis, value)) {
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