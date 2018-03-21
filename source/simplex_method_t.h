//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H
#define RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H


#include <vector>
#include "simplex_definitions.h"
#include "abstract_simplex_task_t.h"
#include "abstract_debuger_t.h"

class simplex_method_t {
protected:
    abstract_simplex_task_t *m_task;
    std::vector<row_t> m_extra_inv_table;
    std::vector<int> m_basis;
    std::vector<row_t> m_columns;

public:
    explicit simplex_method_t(abstract_simplex_task_t *task);

    real_t find_dual_variable(int index);
    real_t find_estimate(int index);

    int find_best_column();
    row_t get_multiplied_column(int index);
    int find_worth_row(int best_column);

    void exchange_variables(int new_index, int row_index);

    bool is_solution_optimal();
    bool is_solution_not_bounded();

    bool solve(abstract_debuger_t *debuger = nullptr);

    row_t get_dual_variables();
    real_t get_x(int index);
    row_t get_column(int index);
    int get_basis(int index);
    abstract_simplex_task_t *get_task();
};


#endif //RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H
