#include <iostream>
#include <vector>
#include <limits>
#include "source/simplex_task_t.h"

int main() {
//    row_t costs = { 4, 5, 4 };
//    std::vector<simplex_method_unequality_t> unequalities;
//    unequalities.emplace_back(row_t {2, 3, 6}, 240.0, simplex_method_unequality_t::type_t::LESS);
//    unequalities.emplace_back(row_t {4, 2, 4}, 200.0, simplex_method_unequality_t::type_t::LESS);
//    unequalities.emplace_back(row_t {4, 6, 8}, 160.0, simplex_method_unequality_t::type_t::LESS);

    row_t costs = { 2, 1, -2};
    std::vector<simplex_method_unequality_t> unequalities;
    unequalities.emplace_back(row_t {1, 1, -1}, 8.0, simplex_method_unequality_t::type_t::GREATER);
    unequalities.emplace_back(row_t {1, -1, 2}, 2.0, simplex_method_unequality_t::type_t::GREATER);
    unequalities.emplace_back(row_t {-2, -8, 3}, 1.0, simplex_method_unequality_t::type_t::GREATER);
//    row_t costs = { 2, 3};
//    std::vector<simplex_method_unequality_t> unequalities;
//    unequalities.emplace_back(row_t {-2, 6}, 40.0, simplex_method_unequality_t::type_t::EQUAL);
//    unequalities.emplace_back(row_t {3, 2}, 28.0, simplex_method_unequality_t::type_t::EQUAL);
//    unequalities.emplace_back(row_t {2, -1}, 14.0, simplex_method_unequality_t::type_t::EQUAL);

//    row_t costs = { -2, 3, -6, -1};
//    std::vector<simplex_method_unequality_t> unequalities;
//    unequalities.emplace_back(row_t {2, 1, -2, 1}, 24.0, simplex_method_unequality_t::type_t::EQUAL);
//    unequalities.emplace_back(row_t {-1, -2, -4, 0}, 22.0, simplex_method_unequality_t::type_t::EQUAL);
//    unequalities.emplace_back(row_t {1, -1, 2, 0}, 10.0, simplex_method_unequality_t::type_t::EQUAL);
    auto task = new simplex_task_t(costs, unequalities);
    auto simplex_method = new simplex_method_t(task);

    row_t solution;
    if (simplex_method->get_solution(solution)) {
        for (auto x : solution) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No solution" << std::endl;
    }

    return 0;
}