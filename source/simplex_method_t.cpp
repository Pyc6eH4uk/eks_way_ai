//
// Created by pyc6eh4uk on 09.03.18.
//

#include <iostream>
#include <iomanip>
#include "simplex_method_t.h"

//
// Created by pyc6eh4uk on 09.03.18.
//

#include <iostream>
#include "simplex_method_t.h"

simplex_method_t::simplex_method_t(abstract_simplex_task_t *task) {
    m_task = task;
    m_extra_inv_table.resize(task->basis_size());
    m_columns.resize(task->basis_size());
    for (int i = 0; i < task->basis_size(); i++) {
        m_extra_inv_table[i].push_back(task->get_equality(i));
        for (int j = 0; j < task->basis_size(); j++)
            m_extra_inv_table[i].push_back(i == j);
        m_extra_inv_table[i].push_back(0);
        m_basis.push_back(task->basis_size() + i);
    }
}

real_t simplex_method_t::find_dual_variable(int index) {
    real_t value = 0;
    for (int j = 0; j < m_task->basis_size(); j++) {
        value += m_task->get_cost(m_basis[j]) * m_extra_inv_table[j][index + 1];
    }
    return value;
}

real_t simplex_method_t::find_estimate(int index) {
    auto column = m_task->get_column(index, get_dual_variables());
    real_t value = 0;
    for (int i = 0; i < m_task->basis_size(); i++) {
        value += find_dual_variable(i) * column[i];
    }
    return value - m_task->get_cost(index);
}

int simplex_method_t::find_best_column() {
    real_t minimal_value = 123.0;
    int minimal_index = -1;
    for (int i = 0; i < m_task->original_variable_size(); i++) {
        real_t value = find_estimate(i);
        if (value < minimal_value) {
            minimal_value = value;
            minimal_index = i;
        }
    }
    return minimal_index;
}

row_t simplex_method_t::get_multiplied_column(int index) {
    row_t column = m_task->get_column(index, get_dual_variables());
    row_t result(m_task->basis_size(), 0);
    for (int i = 0; i < m_task->basis_size(); i++) {
        for (int j = 0; j < m_task->basis_size(); j++) {
            result[i] += m_extra_inv_table[i][j + 1] * column[j];
        }
    }
    return result;
}

int simplex_method_t::find_worth_row(int best_column) {
    row_t column = get_multiplied_column(best_column);
    real_t minimal_value = 0.0;
    int minimal_index = -1;
    for (int i = 0; i < m_task->basis_size(); i++) {
        if (column[i] <= 0) continue;
        real_t value = m_extra_inv_table[i][0] / column[i];
        if (minimal_index == -1 || value < minimal_value) {
            minimal_value = value;
            minimal_index = i;
        }
    }
    return minimal_index;
}

void simplex_method_t::exchange_variables(int new_index, int row_index) {
    row_t column = get_multiplied_column(new_index);
    m_columns[row_index] = m_task->get_column(new_index, get_dual_variables());
    for (int i = 0; i < m_task->basis_size(); i++)
        m_extra_inv_table[i][m_task->basis_size() + 1] = column[i];
    auto m = m_task->basis_size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= m; j++) {
            if (i != row_index) {
                m_extra_inv_table[i][j] -= m_extra_inv_table[row_index][j] * m_extra_inv_table[i][m + 1] /
                                           m_extra_inv_table[row_index][m + 1];
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= m; j++) {
            if (i == row_index) {
                m_extra_inv_table[i][j] /= m_extra_inv_table[i][m + 1];
            }
        }
    }
    m_basis[row_index] = new_index;
}

bool simplex_method_t::is_solution_optimal() {
    auto index = find_best_column();
    auto estimate = find_estimate(index);
    return estimate >= - 1e-6;
}

bool simplex_method_t::is_solution_not_bounded() {
    auto index = find_best_column();
    return find_worth_row(index) == -1;
}

bool simplex_method_t::solve(abstract_debuger_t *debuger) {
    int iteration = 0;

    while (!is_solution_optimal()) {
        if (is_solution_not_bounded())
            return false;

        auto j = find_best_column();
        auto i = find_worth_row(j);
        exchange_variables(j, i);

        if (debuger != nullptr)
            debuger->debug(iteration, this);
        iteration += 1;
    }

    return !is_solution_not_bounded();
}

row_t simplex_method_t::get_dual_variables() {
    row_t dual(m_task->variable_size());
    for (int i = 0; i < m_task->variable_size(); i++)
        dual[i] = find_dual_variable(i);
    return dual;
}

real_t simplex_method_t::get_x(int index) {
    return m_extra_inv_table[index][0];
}


row_t simplex_method_t::get_column(int index) {
    return m_columns[index];
}

int simplex_method_t::get_basis(int index) {
    return m_basis[index];
}

abstract_simplex_task_t *simplex_method_t::get_task() {
    return m_task;
}
