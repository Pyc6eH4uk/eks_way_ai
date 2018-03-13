//
// Created by pyc6eh4uk on 09.03.18.
//

#ifndef RUSLAN_DEBIL_REFACTOR_DEFAULT_SIMPLEX_METHOD_T_H
#define RUSLAN_DEBIL_REFACTOR_DEFAULT_SIMPLEX_METHOD_T_H

#include <iostream>
#include <iomanip>
#include "abstract_simplex_task_t.h"
#include "simplex_method_unequality_t.h"
#include "simplex_method_t.h"

struct simplex_task_t : public abstract_simplex_task_t {
    row_t cost_vector;
    std::vector<simplex_method_equality_t> equalities;

    simplex_task_t(const row_t &costs,
                   const std::vector<simplex_method_unequality_t> &unequalities) {
        cost_vector = costs;
        equalities = simplex_method_unequality_t::to_canonical(unequalities);
        for (int i = 0; i < equalities.size(); i++) {
            cost_vector.push_back(0);
        }
        for (int i = 0; i < equalities.size(); i++) {
            cost_vector.push_back(-100.0);
            std::vector<real_t> extra_row(equalities.size(), 0);
            extra_row[i] = 1.0;
            equalities[i].coefficients.insert(equalities[i].coefficients.end(), extra_row.begin(), extra_row.end());
        }
    }

    double get_cost(int index) const override {
        return cost_vector[index];
    }

    double get_equality(int index) const override {
        return equalities[index].right_side_value;
    }

    int original_variable_size() const override {
        return (int) (cost_vector.size() - equalities.size());
    }

    int variable_size() const override {
        return (int) cost_vector.size();
    }

    int basis_size() const override {
        return (int) equalities.size();
    }

    row_t get_column(int index) const override {
        row_t column;
        for (auto &equalitie : equalities) {
            column.push_back(equalitie.coefficients[index]);
        }
        return column;
    }

    void print_cost() const override {
        int length = (int) cost_vector.size();
        std::cout << "cost:" << std::endl;
        for (int i = 0; i < length; i++) {
            std::cout << std::setw(4) << cost_vector[i] << " ";
        }
        std::cout << std::endl;
    }

    void print_equality() const override {
        int length = (int) equalities.size();
        std::cout << "equalities:" << std::endl;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < equalities[i].coefficients.size(); j++) {
                std::cout << std::setw(4) << equalities[i].coefficients[j] << " ";
            }
            std::cout << " = " << equalities[i].right_side_value << " ";
            std::cout << std::endl;
        }
    }
};


#endif //RUSLAN_DEBIL_REFACTOR_DEFAULT_SIMPLEX_METHOD_T_H
