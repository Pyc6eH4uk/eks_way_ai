//
// Created by gdhsnlvr on 16.03.18.
//

#ifndef EKS_WAY_AI_LINEAR_CUT_SIMPLEX_METHOD_T_H
#define EKS_WAY_AI_LINEAR_CUT_SIMPLEX_METHOD_T_H


#include "simplex_method_t.h"
#include "linear_cut_task_t.h"

class linear_cut_simplex_method_t : public simplex_method_t {
public:
    linear_cut_simplex_method_t(linear_cut_task_t *task);

    real_t find_estimate(int index) override;

    row_t get_multiplied_column(int index) override;

    void get_solution(row_t &x, std::vector<int> &basis, real_t &value) override;

    bool is_solution_optimal() override;
};


#endif //EKS_WAY_AI_LINEAR_CUT_SIMPLEX_METHOD_T_H
