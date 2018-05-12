//
// Created by pyc6eh4uk on 21.03.18.
//

#include "linear_cut_debuger_t.h"
#include "linear_cut_task_t.h"

void linear_cut_debuger_t::debug(int iteration, simplex_method_t *simplex_method) {
    auto task = (linear_cut_task_t*) simplex_method->get_task();

//    std::cout.setf(std::ios::fixed | std::ios::showpoint);
//    std::cout.precision(2);
//    std::cout << "Iteration " << iteration << std::endl;
    real_t value = 0;
    for (int i = 0; i < task->basis_size(); i++) {
        auto x = simplex_method->get_x(i);
        value += x * task->get_cost(simplex_method->get_basis(i));
    }
//    std::cout << "value: " << std::setw(6) << - value << std::endl;
    for (int i = 0; i < task->basis_size(); i++) {
        auto column = simplex_method->get_column(i);
        auto x = simplex_method->get_x(i);
        if (simplex_method->get_basis(i) >= task->get_packages().size())
            continue;
        if (column.empty())
            continue;
//        std::cout << "package: " << std::setw(6) << simplex_method->get_basis(i) << " ";
//        std::cout << "x: " << std::setw(6) << x << " ";
//        std::cout << "cut: ";
//        for (int j = 0; j < task->get_patterns().size(); j++) {
//            std::cout << std::setw(6) << column[j] << " ";
//        }
//        std::cout << std::endl;
    }
}
