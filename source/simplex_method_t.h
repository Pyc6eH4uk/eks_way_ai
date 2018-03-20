//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H
#define RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H


#include <vector>
#include "simplex_definitions.h"
#include "abstract_simplex_task_t.h"

class simplex_method_t {
protected:
    abstract_simplex_task_t *m_task;
    std::vector<row_t> m_extra_inv_table;
    std::vector<int> m_basis;

public:
    explicit simplex_method_t(abstract_simplex_task_t *task);

    virtual real_t find_dual_variable(int index);
    virtual real_t find_estimate(int index);

    virtual int find_best_column();
    virtual row_t get_multiplied_column(int index);
    virtual int find_worth_row(int best_column);

    virtual void exchange_variables(int new_index, int row_index);

    virtual bool is_solution_optimal();
    virtual bool is_solution_not_bounded();

    virtual bool get_solution(row_t &x, std::vector<int> &basis, real_t &value);
    row_t get_dual_variables();

    void print_inv_table();
    void debug(int iteration, const row_t &column);
};


#endif //RUSLAN_DEBIL_REFACTOR_ABSTRACT_SIMPLEX_METHOD_T_H
