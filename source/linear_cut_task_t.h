//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_LINEAR_CUT_TASK_T_H
#define RUSLAN_DEBIL_REFACTOR_LINEAR_CUT_TASK_T_H


#include "abstract_simplex_task_t.h"

class linear_cut_task_t : public abstract_simplex_task_t {
public:
    struct package_t {
        int length;
        int low_size;
        int high_size;
    };

protected:
    std::vector<package_t> packages;
    std::vector<package_t> patterns;

public:
    linear_cut_task_t(const std::vector<package_t> &packages,
                      const std::vector<package_t> &patterns);

    std::vector<int> find_linear_cut(int index, const row_t &v);

    double get_cost(int index) const override;
    double get_equality(int index) const override;
    row_t get_column(int index) const override;
    int variable_size() const override;
    int original_variable_size() const override;
    int basis_size() const override;
};


#endif //RUSLAN_DEBIL_REFACTOR_LINEAR_CUT_TASK_T_H
