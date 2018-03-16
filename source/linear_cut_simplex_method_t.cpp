//
// Created by gdhsnlvr on 16.03.18.
//

#include "linear_cut_simplex_method_t.h"

linear_cut_simplex_method_t::linear_cut_simplex_method_t(linear_cut_task_t *task) : simplex_method_t(task) {

}

real_t linear_cut_simplex_method_t::find_estimate(int index) {
    auto task = (linear_cut_task_t*) m_task;
    row_t costs;
    for (int i = 0; i < task->get_patterns().size(); i++) {
        costs.push_back(find_dual_variable(i));
    }

    auto cut = task->find_linear_cut(index, costs);
    real_t value = 0;
    for (int j = 0; j < task->basis_size(); j++) {
        value += costs[j] * cut[j];
    }
    return value + task->get_cost(index) + m_extra_inv_table[index][m_task->basis_size() + 1];
}

row_t linear_cut_simplex_method_t::get_multiplied_column(int index) {
    auto task = (linear_cut_task_t*) m_task;
    row_t costs;
    for (int i = 0; i < task->get_patterns().size(); i++) {
        costs.push_back(find_dual_variable(i));
    }

    auto cut = task->find_linear_cut(index, costs);
    row_t result(task->basis_size(), 0);
    for (int i = 0; i < task->basis_size(); i++) {
        for (int j = 0; j < task->basis_size(); j++) {
            result[i] += m_extra_inv_table[i][j + 1] * cut[j];
        }
    }
    return result;
}

void linear_cut_simplex_method_t::get_solution(row_t &x, std::vector<int> &basis, real_t &value) {
    x.clear();
    x.resize(m_task->variable_size(), 0);
    basis.clear();
    value = 0.0;
    for (int i = 0; i < m_basis.size(); i++) {
        x[i] = m_extra_inv_table[i][0];
        basis.push_back(i);
        value += x[i] * m_task->get_cost(i);
    }
}

bool linear_cut_simplex_method_t::is_solution_optimal() {
    real_t estimate = 0.0;
    for (int i = 0; i < m_basis.size(); i++) {
        estimate += m_extra_inv_table[i][m_basis.size() + 1];
    }
    return estimate <= 1.0 + 1e-6;
}

